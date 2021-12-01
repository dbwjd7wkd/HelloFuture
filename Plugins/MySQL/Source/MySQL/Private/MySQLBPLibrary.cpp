// Copyright 2021, Athian Games. All Rights Reserved. 


#include "MySQLBPLibrary.h"
#include "XmlParser.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "Serialization/BufferArchive.h"
#include "Templates/SharedPointer.h"
#include "HAL/PlatformFilemanager.h"
#include "Logging/LogMacros.h"
#include "Logging/LogTrace.h"
#include "DLLManager.h"
#include <exception>
#include <vector>


IImageWrapperModule* ImageWrapperModule = NULL;




bool UMySQLBPLibrary::GetOpenFileDialogue(TArray<FString>& FileNames, FString DialogueTitle, FString FileTypes, bool multiselect)
{
#if PLATFORM_WINDOWS
	if (DLLManager::LoadDLL("FileBrowser.dll"))
	{
		FileNames = DLLManager::GetOpenFileDialogue(DialogueTitle, FileTypes, multiselect);
		if (FileNames.Num() > 0)
		{
			DLLManager::UnLoadDLL();
			return true;
		}

	}

	DLLManager::UnLoadDLL();
	return false;

#elif PLATFORM_MAC

	return false;

#elif PLATFORM_LINUX

	return false;

#elif PLATFORM_IOS

	return false;

#elif PLATFORM_ANDROID

	return false;

#else

	return false;

#endif
}



void FlushImageRenderingCommands(bool bFlushDeferredDeletes)
{
	if (!GIsRHIInitialized)
	{
		return;
	}

	// Need to flush GT because render commands from threads other than GT are sent to
	// the main queue of GT when RT is disabled
	if (!GIsThreadedRendering
		&& !FTaskGraphInterface::Get().IsThreadProcessingTasks(ENamedThreads::GameThread)
		&& !FTaskGraphInterface::Get().IsThreadProcessingTasks(ENamedThreads::GameThread_Local))
	{
		FTaskGraphInterface::Get().ProcessThreadUntilIdle(ENamedThreads::GameThread);
		FTaskGraphInterface::Get().ProcessThreadUntilIdle(ENamedThreads::GameThread_Local);
	}

	ENQUEUE_RENDER_COMMAND(FlushPendingDeleteRHIResourcesCmd)(
		[bFlushDeferredDeletes](FRHICommandListImmediate& RHICmdList)
	{
		RHICmdList.ImmediateFlush(
			bFlushDeferredDeletes ?
			EImmediateFlushType::FlushRHIThreadFlushResourcesFlushDeferredDeletes :
			EImmediateFlushType::FlushRHIThreadFlushResources);
	});


	// Find the objects which may be cleaned up once the rendering thread command queue has been flushed.
	FPendingCleanupObjects* PendingCleanupObjects = GetPendingCleanupObjects();

	// Issue a fence command to the rendering thread and wait for it to complete.
	FRenderCommandFence Fence;
	Fence.BeginFence();
	Fence.Wait();

	// Delete the objects which were enqueued for deferred cleanup before the command queue flush.
	delete PendingCleanupObjects;
}

void GetTexturePixels(UTexture2D* Texture, TArray<FColor>& OutPixels)
{

	OutPixels.Reset();

	ENQUEUE_RENDER_COMMAND(FSaveMySQLImageResource)(
		[OutPixels, Texture](FRHICommandListImmediate& RHICmdList)
	{
		TArray<FColor> OutData = OutPixels;
		FTextureResource* TextureResource = Texture->Resource;
		FTexture2DRHIRef Texture2DRHIRef = TextureResource->TextureRHI->GetTexture2D();

		FIntRect Rect = FIntRect(0, 0, Texture->GetImportedSize().X, Texture->GetImportedSize().Y);
		FReadSurfaceDataFlags Flags = FReadSurfaceDataFlags(RCM_UNorm, CubeFace_MAX);
		
		RHICmdList.ReadSurfaceData(
			Texture2DRHIRef,
			Rect,
			OutData,
			Flags
		);
	});

	FlushImageRenderingCommands(false);
}


UTexture2D* UMySQLBPLibrary::LoadTexturefromCharData(char* ImageChar)
{
	CreateImageWrapperModule();

	if (ImageWrapperModule)
	{

		TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule->CreateImageWrapper(EImageFormat::PNG);

		int length = size_t(ImageChar);
		TArray<uint8>  CompressedImageData;
		CompressedImageData.AddUninitialized(length);
		for (int i = 0; i < length; i++)
		{
			CompressedImageData[i] = ImageChar[i];
		}

		if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(CompressedImageData.GetData(), CompressedImageData.Num()))
		{
			TArray<uint8> UncompressedBGRA;
			if (ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA))
			{
				UTexture2D* Texture = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_B8G8R8A8);

				if (Texture)
				{

					void* TextureData = Texture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
					FMemory::Memcpy(TextureData, UncompressedBGRA.GetData(), UncompressedBGRA.Num());
					Texture->PlatformData->Mips[0].BulkData.Unlock();

					Texture->UpdateResource();
					return Texture;
				}
			}
		}
	}

	return NULL;

}


char* UMySQLBPLibrary::GetCharFromTextureData(UTexture2D *Texture, FString Path)
{
	FVector2D ImageSize = FVector2D(Texture->GetSurfaceWidth(), Texture->GetSurfaceHeight());
	char* imagebytes = new char[ImageSize.X * ImageSize.Y * 4];


	if (Texture->PlatformData->Mips.Num() > 0)
	{
		TextureCompressionSettings OldCompressionSettings = Texture->CompressionSettings;
#if WITH_EDITORONLY_DATA
		TextureMipGenSettings OldMipGenSettings = Texture->MipGenSettings;
#endif
		bool OldSRGB = Texture->SRGB;

		Texture->CompressionSettings = TextureCompressionSettings::TC_VectorDisplacementmap;
#if WITH_EDITORONLY_DATA
		Texture->MipGenSettings = TextureMipGenSettings::TMGS_NoMipmaps;
#endif	
		
		Texture->SRGB = false;
		Texture->UpdateResource();

		FTexture2DMipMap* Mip = &Texture->PlatformData->Mips[0];

		uint8* TextureData = (uint8*)Mip->BulkData.Lock(LOCK_READ_WRITE);
		
		//TArray<uint8> OutArray;
		//OutArray.InsertZeroed(0, ImageSize.X*ImageSize.Y*4);

		for (int i = 0; i < (ImageSize.X*ImageSize.Y); i+=4)
		{
			imagebytes[i] = TextureData[i];
			imagebytes[i + 1] = TextureData[i+ 1];
			imagebytes[i + 2] = TextureData[i + 2];
			imagebytes[i + 3] = TextureData[i + 3];

		}


		TArray<FColor> OutPixels;
		GetTexturePixels(Texture, OutPixels);


		//FFileHelper::SaveArrayToFile(OutArray, *Path);
		Texture->CompressionSettings = OldCompressionSettings;
#if WITH_EDITORONLY_DATA
		Texture->MipGenSettings = OldMipGenSettings;
#endif
		Texture->SRGB = OldSRGB;
		
		Mip->BulkData.Unlock();
		Texture->UpdateResource();


	}

	return imagebytes;
}


bool UMySQLBPLibrary::SaveTextureToPath(UTexture2D* Texture, const FString Path)
{

	if (Texture && FPaths::ValidatePath(Path))
	{

		FVector2D ImageSize = FVector2D(Texture->GetSurfaceWidth(), Texture->GetSurfaceHeight());

		char* imagebytes = GetCharFromTextureData(Texture, Path);
		if (imagebytes)
		{
			char* path = TCHAR_TO_ANSI(*Path);
      		return false;
		}

	}
	return false;
}


void UMySQLBPLibrary::UpdateImageFromPath(FString Query, FString UpdateParameter, int ParameterID, FString ImagePath, bool& IsSuccessful, FString& ErrorMessage)
{
	//FString ImageParam = "@" + UpdateParameter;
	//Query = Query.Replace(*ImageParam, *FString("?"));

	//string query(TCHAR_TO_UTF8(*Query));
	//char* q = _strdup(query.c_str());

	//if (DBConnection)
	//{
	//	char* ImageChar = GetRawImageFromPath(ImagePath);

	//	if (ImageChar)
	//	{
	//		
	//		unique_ptr<sql::PreparedStatement> PStatement(DBConnection->prepareStatement(q));
	//		try
	//		{
	//			BlobBuilder BlobBuffer(ImageChar);
	//			istream ImageBlob(&BlobBuffer);
	//			PStatement->setBlob(ParameterID, &ImageBlob);
	//			PStatement->execute();
	//			IsSuccessful = true;

	//		}
	//		catch (const exception& ex)
	//		{
	//			const char* emessage = ex.what();
	//			ErrorMessage = FString(UTF8_TO_TCHAR(emessage));
	//			IsSuccessful = false;

	//		}


	//	}


	//}


}

UTexture2D* UMySQLBPLibrary::SelectImageFromQuery(FString Query, FString SelectParameter, bool& IsSuccessful, FString& ErrorMessage)
{

	//if (DBConnection)
	//{
	//	string query(TCHAR_TO_UTF8(*Query));
	//	char* q = _strdup(query.c_str());

	//	string selectparam(TCHAR_TO_UTF8(*SelectParameter));
	//	char* sparamchar = _strdup(selectparam.c_str());

	//	unique_ptr<sql::PreparedStatement> Statement(DBConnection->prepareStatement(q));
	//	try
	//	{
	//		
	//		sql::ResultSet* result = Statement->executeQuery();

	//		while (result->next())
	//		{
	//			
	//			istream* blobData = result->getBlob(sparamchar);
	//			if (blobData)
	//			{
	//				
	//				blobData->seekg(0, ios::end);
	//				int length = blobData->tellg();
	//				blobData->seekg(0, blobData->beg);

	//				
	//				char* ImageChar = new char[length];
	//				blobData->read(ImageChar, length);

	//				if (ImageChar)
	//				{
	//					UTexture2D* Texture = LoadTexturefromCharData(ImageChar);
	//					IsSuccessful = true;
	//					return  Texture;
	//				}
	//			}

	//		}

	//	}
	//	catch (const exception& ex)
	//	{
	//		const char* emessage = ex.what();
	//		ErrorMessage = FString(UTF8_TO_TCHAR(emessage));

	//	}

	//}

	IsSuccessful = false;
	return NULL;

}



void UMySQLBPLibrary::CreateImageWrapperModule()
{
	if (!ImageWrapperModule)
	{
		ImageWrapperModule = &FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	}
}

char* UMySQLBPLibrary::GetRawImageFromPath(FString ImagePath)
{
	CreateImageWrapperModule();
	void* imagebytes = nullptr;
	if (ImageWrapperModule)
	{
		FString Extension = FPaths::GetExtension(ImagePath);
		EImageFormat ImageFormat;

		if (Extension.Equals("jpeg", ESearchCase::IgnoreCase) || Extension.Equals("jpg", ESearchCase::IgnoreCase))
		{
			ImageFormat = EImageFormat::JPEG;
		}
		else if (Extension.Equals("png", ESearchCase::IgnoreCase))
		{
			ImageFormat = EImageFormat::PNG;
		}
		else
		{
			ImageFormat = EImageFormat::BMP;
		}

		TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule->CreateImageWrapper(ImageFormat);

		TArray<uint8> RawFileData;
		if (FFileHelper::LoadFileToArray(RawFileData, *ImagePath))
		{
			if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(RawFileData.GetData(), RawFileData.Num()))
			{
				TArray<uint8> UncompressedBGRA;
				if (ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA))
				{
					const int64 RawNum = UncompressedBGRA.Num();
					imagebytes = FMemory::Malloc(RawNum);
					FMemory::Memcpy(imagebytes, UncompressedBGRA.GetData(), RawNum);

				}
			}
		}

	}

	return (char*)imagebytes;
}



