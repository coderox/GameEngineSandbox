#pragma once
#include "scenes/GameScene.h"
#include "textures/ITextureManager.h"
#include "sprites/ISpriteRenderer.h"
#include <memory>

class SplashScene : public Engine::GameScene 
{
public:
    SplashScene();
    ~SplashScene();
    void Load();
	void Unload();
	void UpdateScreenSize(int width, int height);
	void Update(Utilities::StepTimer const& timer);
	void Draw(Utilities::StepTimer const& timer);

private:
	std::shared_ptr<Engine::Sprite> mSprite;
	float mMillisecondsToLoad;
	bool hasLoadedGamePlay;

	std::shared_ptr<Engine::ITextureManager> mTextureManager;
    std::shared_ptr<Engine::ISpriteRenderer> mSpriteRenderer;
};