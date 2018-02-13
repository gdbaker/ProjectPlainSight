// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//#include "FindSessionsCallbackProxy.h"
#include "Engine.h"
#include "UnrealNetwork.h"
#include "Online.h"
#include "Engine/GameInstance.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UI/MenuUserWidget.h"
#include "PlainSightGameInstance.generated.h"



#define SETTING_SERVER_NAME FName(TEXT("SERVERNAMEKEY"))

USTRUCT(BlueprintType)
struct FSessionResult
{
	GENERATED_USTRUCT_BODY()

	//session
	FOnlineSessionSearchResult ChosenSession;

	//ping
	UPROPERTY(BlueprintReadOnly)
	int32 PingInMs;

	//ServerName
	UPROPERTY(BlueprintReadOnly)
	FString ServerName;

	//number of available slots
	UPROPERTY(BlueprintReadOnly)
	int32 NumOpenConnections;

	//total server size
	UPROPERTY(BlueprintReadOnly)
	int32 NumPossibleConnections;
};

/**
 * 
 */
UCLASS()
class PLAINSIGHT_API UPlainSightGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	/**
	*	Function to host a game!
	*
	*	@Param		UserID			User that started the request
	*	@Param		SessionName		Name of the Session
	*	@Param		bIsLAN			Is this is LAN Game?
	*	@Param		bIsPresence		"Is the Session to create a presence Session"
	*	@Param		MaxNumPlayers	        Number of Maximum allowed players on this "Session" (Server)
	*/
	bool HostSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, FString ServerName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers);
	
	/**
	*	Find an online session
	*
	*	@param UserId user that initiated the request
	*	@param bIsLAN are we searching LAN matches
	*	@param bIsPresence are we searching presence sessions
	*/
	void FindSessions(TSharedPtr<const FUniqueNetId> UserId, bool bIsLAN, bool bIsPresence);

	/**
	*	Joins a session via a search result
	*
	*	@param SessionName name of session
	*	@param SearchResult Session to join
	*
	*	@return bool true if successful, false otherwise
	*/
	bool JoinSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, const FOnlineSessionSearchResult& SearchResult);

	//Constructor
	UPlainSightGameInstance(const FObjectInitializer& ObjectInitializer);

	/* Delegate called when session created */
	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	/* Delegate called when session started */
	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;
	/** Delegate for searching for sessions */
	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;
	/** Delegate for joining a session */
	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;
	/** Delegate for destroying a session */
	FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;

	/** Handles to registered delegates for creating/starting a session */
	FDelegateHandle OnCreateSessionCompleteDelegateHandle;
	FDelegateHandle OnStartSessionCompleteDelegateHandle;
	/** Handle to registered delegate for searching a session */
	FDelegateHandle OnFindSessionsCompleteDelegateHandle;
	/** Handle to registered delegate for joining a session */
	FDelegateHandle OnJoinSessionCompleteDelegateHandle;
	/** Handle to registered delegate for destroying a session */
	FDelegateHandle OnDestroySessionCompleteDelegateHandle;

	//handles settings
	TSharedPtr<class FOnlineSessionSettings> SessionSettings;

	//session search results
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	/**
	*	Function fired when a session create request has completed
	*
	*	@param SessionName the name of the session this callback is for
	*	@param bWasSuccessful true if the async action completed without error, false if there was an error
	*/
	virtual void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

	/**
	*	Function fired when a session start request has completed
	*
	*	@param SessionName the name of the session this callback is for
	*	@param bWasSuccessful true if the async action completed without error, false if there was an error
	*/
	void OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful);

	/**
	*	Delegate fired when a session search query has completed
	*
	*	@param bWasSuccessful true if the async action completed without error, false if there was an error
	*/
	void OnFindSessionsComplete(bool bWasSuccessful);

	/**
	*	Delegate fired when a session join request has completed
	*
	*	@param SessionName the name of the session this callback is for
	*	@param bWasSuccessful true if the async action completed without error, false if there was an error
	*/
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	/**
	*	Delegate fired when a destroying an online session has completed
	*
	*	@param SessionName the name of the session this callback is for
	*	@param bWasSuccessful true if the async action completed without error, false if there was an error
	*/
	virtual void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);

	//menu widget that call find online games
	UUserWidget *MenuWidget;

 public:
	UFUNCTION(BlueprintCallable, Category = "Network")
	void StartOnlineGame();

	UFUNCTION(BlueprintCallable, Category = "Network")
	void FindOnlineGames(UUserWidget *Menu);

	UFUNCTION(BlueprintCallable, Category = "Network")
	TArray<FSessionResult> GetSessionsList();

	UFUNCTION(BlueprintCallable, Category = "Network")
	void JoinOnlineGame(FSessionResult chosenSession);

	UFUNCTION(BlueprintCallable, Category = "Network")
	void DestroySessionAndLeaveGame();
};
