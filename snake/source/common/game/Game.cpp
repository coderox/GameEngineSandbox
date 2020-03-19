#include "Game.h"
#include "IOC.hpp"
#include "scenes/SplashScene.h"
#include "scenes/GamePlayScene.h"
#include "scenes/GameOverScene.h"
#include "scenes/PauseScene.h"
#include "scenes/ISceneManager.h"
#include "url\UrlParser.h"

using namespace std;
using namespace Utilities;
using namespace Engine;

Game::Game() 
	: mCurrentState(GameState::Unknown)
	, mNextState(GameState::Unknown)
{

}

void Game::Initialize()
{
	mSceneManager = IOCContainer::Instance().Resolve<ISceneManager>();
	auto url = std::make_shared<Engine::UrlParser>(L"http://www.coderox.se/blog");
	auto domain = url->GetDomain();
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
			mNextState = GameState::Splash;
		}
		break;

	case GameState::Splash:
		if(mCurrentState == GameState::Boot)
		{
			mCurrentState = GameState::Splash;
			mSceneManager->AddScene(make_shared<SplashScene>(this));
		}
		break;

	case GameState::GamePlay:
		if(mCurrentState == GameState::Splash) {
			mSceneManager->AddScene(make_shared<GamePlayScene>(this));
			mSceneManager->RemoveScene(typeid(SplashScene));
		}
		else if (mCurrentState == GameState::GameOver) {
			mSceneManager->AddScene(make_shared<GamePlayScene>(this));
			mSceneManager->RemoveScene(typeid(GameOverScene));
		}
		else if (mCurrentState == GameState::Pause) {
			mSceneManager->RemoveScene(typeid(PauseScene));
		}
		mCurrentState = GameState::GamePlay;
		break;

	case GameState::GameOver:
		if (mCurrentState == GameState::GamePlay) {
			mCurrentState = GameState::GameOver;
			mSceneManager->AddScene(make_shared<GameOverScene>(this));
			mSceneManager->RemoveScene(typeid(GamePlayScene));
		}
		break;

	case GameState::Pause:
		if (mCurrentState == GameState::GamePlay) {
			mCurrentState = GameState::Pause;
			mSceneManager->AddScene(make_shared<PauseScene>());
		}
		break;

	case GameState::Menu:
	case GameState::Loading:
	default:
		break;
	}
}

void Game::GoToState(GameState gameState) 
{
	mNextState = gameState;
}