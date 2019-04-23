#include "SplashScene.h"
#include "textures/TextureManager.h"
#include "IOC.hpp"
#include "scenes/ISceneManager.h"
#include "GamePlayScene.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

SplashScene::SplashScene()
	: mSprite(make_shared<Sprite>())
	, mMillisecondsToLoad(1000.0f)
	, hasLoadedGamePlay(false)
{
	ID = "SplashScene";
}

SplashScene::~SplashScene()
{

}

void SplashScene::Load()
{
	mTextureManager = IOCContainer::Instance().Resolve<ITextureManager>();
    mSpriteRenderer = IOCContainer::Instance().Resolve<ISpriteRenderer>();
    
	vector<wstring> filenames;
	filenames.emplace_back(L"splash.png");
	filenames.emplace_back(L"apple.png");
	mTextureManager->LoadTextures(vector<wstring>(filenames));

	mSprite->Texture = mTextureManager->GetTexture(L"splash.png");
}

void SplashScene::Unload()
{

}

void SplashScene::UpdateScreenSize(int width, int height) 
{
	mSprite->Height = height;
	mSprite->Width = width;
	mSprite->Position = { 0.0f, 0.0f };

}

void SplashScene::Update(shared_ptr<IStepTimer> timer)
{
	mMillisecondsToLoad -= static_cast<float>((timer->GetElapsedSeconds() * 1000.0f));
	if (mMillisecondsToLoad <= 0) {
		auto sceneManager = IOCContainer::Instance().Resolve<ISceneManager>();
		if (!hasLoadedGamePlay) {
			sceneManager->AddScene(make_shared<GamePlayScene>());
			hasLoadedGamePlay = true;
		//	mMillisecondsToLoad = 2000.0f;
		//}
		//else {
			sceneManager->RemoveScene(ID);
		}
	}
}

void SplashScene::Draw(shared_ptr<IStepTimer> /*timer*/)
{
	if (mSpriteRenderer) {
		mSpriteRenderer->DrawSprite(mSprite);
	}
}