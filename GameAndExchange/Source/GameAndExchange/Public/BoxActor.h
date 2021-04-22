// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Core/Public/Containers/Array.h"
#include "BoxActor.generated.h"

#define PCLOG(X) UE_LOG(LogTemp,Warning,TEXT("%s"),X)


UENUM(BlueprintType)
enum class EMoveDir :uint8
{
	up = 0,

	down = 1,

	left = 2,

	right = 3

};


USTRUCT()
struct FManagerBoxPos
{
	GENERATED_USTRUCT_BODY();
	TArray<bool> XMerge;//��¼�Ͳ�ѯ�ĸ�x�᷽�����Ƿ�ϲ���һ��
	TArray<bool> YMerge;//��¼�Ͳ�ѯ�ĸ�y�᷽�����Ƿ�ϲ���һ��
	TArray<TArray<class ABoxActor*>> MPlaced;//��¼�Ͳ�ѯ4*4�������Ƿ�ռ��
	FManagerBoxPos(const int w) {
		XMerge.Init(false, w);
		YMerge.Init(false, w);
		TArray<class ABoxActor*> tmp;
		tmp.Init(nullptr, w);
		MPlaced.Init(tmp, w);

	}
	FManagerBoxPos() {};
};



UCLASS()
class GAMEANDEXCHANGE_API ABoxActor : public AActor
{
	GENERATED_BODY()
public:
	//
	void InitCheckerBoard(FString CubePath, FString MaterialsPath, class AManagerCheckerBoard* inclass);
	FVector2D MakeBoxPos();
	void BroadCastFunc(EMoveDir inInputDir);

	void UpHitEvent(ABoxActor& SelfActor, ABoxActor& OtherActor);
	void DownHitEvent(ABoxActor& SelfActor, ABoxActor& OtherActor);
	void LeftHitEvent(ABoxActor& SelfActor, ABoxActor& OtherActor);
	void RightHitEvent(ABoxActor& SelfActor, ABoxActor& OtherActor);

	FVector2D& GetPos() {return normalPosition;}
	void CreateNewBox(int numbers);

	//oporated func
	void MoveUp(int Maxwd, int stepy);
	void MoveDown(int Maxwd, int stepy);
	void MoveLeft(int Maxwd,int stepx);
	void MoveRight(int Maxwd, int stepx);

	void setCompute(bool inCompute) { Compute = inCompute; }
	bool GetCompute() { return Compute; }

	void SetScore() { BoxScore*=2; }
	int GetScore() { return BoxScore; }
	
public:	
	// Sets default values for this actor's properties
	ABoxActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
protected:
	//���̵ĳ�ʼλ���趨
	FVector local=FVector(0,0,0);

	int Boxwd;//��������

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	//ÿһ����������ʱ��ĳ�ʼ����ֵ
	FVector2D  normalPosition;
	bool Compute = false;
	//��ǰBox�ķ���
	UPROPERTY(EditAnywhere)
	int BoxScore;
	UPROPERTY(EditAnywhere)
	class USceneComponent* Root_Component;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* SM_Component;
	class UStaticMesh* SMCube;
	class UMaterial* M_flower;
	class UTextRenderComponent* TextCom;

		
	

};



