#include "Game.h"
#include "IOC.hpp"
#include "scenes/SceneManager.h"
#include "scenes/SplashScene.h"
#include "scenes/GamePlayScene.h"
#include "scenes/ISceneManager.h"

using namespace std;
using namespace Utilities;
using namespace Engine;

Game::Game() 
	: mSceneManager(make_shared<SceneManager>())
	, mCurrentState(GameState::Unknown)
	, mNextState(GameState::Unknown)
{

}

void Game::Initialize()
{
	// Initialize
	mSceneManager->Initialize();
}

void Game::UpdateScreenSize(int width, int height)
{
    mSceneManager->UpdateScreenSize(width, height);
}

void Game::Update(shared_ptr<IStepTimer> timer)
{
	switch (mNextState)
	{
	case GameState::Unknown:
		if(mCurrentState == GameState::Unknown)
		{
			mNextState = GameState::Boot;
		}
		break;

	case GameState::Boot:
		if(mCurrentState == GameState::Unknown)
		{
			mCurrentState = GameState::Boot;
			mNextState = GameState::SplashScreen;
		}
		break;

	case GameState::SplashScreen:
		if(mCurrentState == GameState::Boot)
		{
			mCurrentState = GameState::SplashScreen;
			mSceneManager->AddScene(make_shared<SplashScene>(this));
		}
		break;

	case GameState::GamePlay:
		if(mCurrentState == GameState::SplashScreen) {
			mCurrentState = GameState::GamePlay;
			mSceneManager->AddScene(make_shared<GamePlayScene>(this));
			mSceneManager->RemoveScene("SplashScene");
		}
		break;

	case GameState::Menu:
	case GameState::Pause:
	case GameState::GameOver:
	case GameState::Loading:
	default:
		break;
	}
	mSceneManager->Update(timer);
}

void Game::Draw(shared_ptr<IStepTimer> timer)
{
   	mSceneManager->Draw(timer);
}

void Game::GoToState(GameState gameState) 
{
	mNextState = gameState;
}