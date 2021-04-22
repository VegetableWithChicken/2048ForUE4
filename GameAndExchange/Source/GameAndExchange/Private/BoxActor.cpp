// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxActor.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Engine/StaticMesh.h"
#include "Runtime/Engine/Classes/Materials/Material.h"
#include "Runtime/Engine/Classes/Components/SceneComponent.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectGlobals.h"
#include "ManagerCheckerBoard.h"
#include "Runtime/Core/Public/Delegates/Delegate.h"
#include "Engine/Classes/Components/TextRenderComponent.h"

class AManagerCheckerBoard* MCheckBoardIns = nullptr;
//���ӹ���һ��������Ϣ
FManagerBoxPos ManagerBoxPos;
//�������ӵ�·��
FString CubePath;
FString MaterialsPath;

void ABoxActor::InitCheckerBoard(FString inCubePath, FString inMaterialsPath, AManagerCheckerBoard* inclass)
{
	MCheckBoardIns = inclass;
	if (MCheckBoardIns)
	{
		ManagerBoxPos=FManagerBoxPos(MCheckBoardIns->wd);
		CubePath = inCubePath;
		MaterialsPath = inMaterialsPath;
		
		CreateNewBox(2);

	}
	else { return; }
	


}
void ABoxActor::CreateNewBox(int numbers)
{
	FRotator rot = FRotator();
	for (int t = 0; t < numbers; ++t)
	{
		FVector2D pos = MakeBoxPos();
		FVector loc = FVector(pos.X * 100, pos.Y * 100, 0);
		ABoxActor* InitBox = GWorld->SpawnActor<ABoxActor>(ABoxActor::StaticClass(), loc, rot);
		ManagerBoxPos.MPlaced[pos.X][pos.Y] = InitBox;
		ManagerBoxPos.MPlaced[pos.X][pos.Y]->GetPos().X = pos.X;
		ManagerBoxPos.MPlaced[pos.X][pos.Y]->GetPos().Y = pos.Y;
		InitBox->Boxwd = MCheckBoardIns->wd;
		InitBox->BoxScore = FMath::RandRange(1, 9) > 7 ? 4 : 2;
		InitBox->TextCom->SetText(FText::FromString(FString::FromInt(InitBox->GetScore())));
		InitBox->setCompute(false);
		MCheckBoardIns->CallBoxEvent.AddUObject(InitBox, &ABoxActor::BroadCastFunc);
	}
}

void ABoxActor::BroadCastFunc(EMoveDir inInputDir)
{
	this->setCompute(false);
	switch (inInputDir)
	{
	case EMoveDir::up:
		for (int y = 0; y < Boxwd; ++y)
		{
			MoveUp(Boxwd,y);
		}
		break;

	case EMoveDir::down:
		for (int y = 0; y < Boxwd; ++y)
		{
			MoveDown(Boxwd,y);
		}
		break;

	case EMoveDir::left:
		for (int x = 0; x < Boxwd; ++x)
		{
		   MoveLeft(Boxwd, x);
		}
		break;

	case EMoveDir::right:
		for (int x = 0; x < Boxwd; ++x)
		{
			MoveRight(Boxwd, x);
		}
		break;

	default:

		break;

	}
}


void ABoxActor::DownHitEvent(ABoxActor& SelfActor, ABoxActor& OtherActor)
{
	if (SelfActor.GetScore() == OtherActor.GetScore()&& !OtherActor.GetCompute() && !SelfActor.GetCompute())
	{
		MCheckBoardIns->SetCanMove();
		SelfActor.SetScore();
		SelfActor.GetScore() > 100 ? SelfActor.TextCom->SetWorldSize(50) : TextCom->SetWorldSize(80);
		SelfActor.TextCom->SetText(FText::FromString(FString::FromInt(SelfActor.GetScore())));

		FVector2D tempvec = SelfActor.GetPos();
		SelfActor.GetPos() =OtherActor.GetPos();
		FVector result = FVector(SelfActor.GetPos().X * 100, SelfActor.GetPos().Y * 100, 0);
		SelfActor.SetActorLocation(OtherActor.GetActorLocation());//actor ǰ��һ��
		ManagerBoxPos.MPlaced[SelfActor.GetPos().X][SelfActor.GetPos().Y] = &SelfActor;
		SelfActor.setCompute(true);
		OtherActor.Destroy();
		ManagerBoxPos.MPlaced[tempvec.X][tempvec.Y]=nullptr;
	}
	else
	{

	}

}
void ABoxActor::UpHitEvent(ABoxActor& SelfActor, ABoxActor& OtherActor)
{
	if (SelfActor.GetScore() == OtherActor.GetScore() && !OtherActor.GetCompute() && !SelfActor.GetCompute())
	{
		MCheckBoardIns->SetCanMove();
		SelfActor.SetScore();
		SelfActor.GetScore() > 100 ? SelfActor.TextCom->SetWorldSize(50) : TextCom->SetWorldSize(80);
		SelfActor.TextCom->SetText(FText::FromString(FString::FromInt(SelfActor.GetScore())));
		FVector2D tempvec = SelfActor.GetPos();
		SelfActor.GetPos() = OtherActor.GetPos();
		FVector result = FVector(SelfActor.GetPos().X * 100, SelfActor.GetPos().Y * 100, 0);
		SelfActor.SetActorLocation(OtherActor.GetActorLocation());//actor ǰ��һ��
		ManagerBoxPos.MPlaced[SelfActor.GetPos().X][SelfActor.GetPos().Y] = &SelfActor;
		SelfActor.setCompute(true);
		OtherActor.Destroy();
		ManagerBoxPos.MPlaced[tempvec.X][tempvec.Y] = nullptr;
	}
	else
	{

	}
}
void ABoxActor::LeftHitEvent(ABoxActor& SelfActor, ABoxActor& OtherActor)
{
	if (SelfActor.GetScore() == OtherActor.GetScore() && !OtherActor.GetCompute() && !SelfActor.GetCompute())
	{
		MCheckBoardIns->SetCanMove();
		SelfActor.SetScore();
		SelfActor.TextCom->SetText(FText::FromString(FString::FromInt(SelfActor.GetScore())));
		SelfActor.GetScore() > 100 ? SelfActor.TextCom->SetWorldSize(50) : TextCom->SetWorldSize(80);
		FVector2D tempvec = SelfActor.GetPos();
		SelfActor.GetPos() = OtherActor.GetPos();
		FVector result = FVector(SelfActor.GetPos().X * 100, SelfActor.GetPos().Y * 100, 0);
		SelfActor.SetActorLocation(OtherActor.GetActorLocation());//actor ǰ��һ��
		ManagerBoxPos.MPlaced[SelfActor.GetPos().X][SelfActor.GetPos().Y] = &SelfActor;
		SelfActor.setCompute(true);
		OtherActor.Destroy();
		ManagerBoxPos.MPlaced[tempvec.X][tempvec.Y] = nullptr;
	}
	else
	{

	}
	
}
void ABoxActor::RightHitEvent(ABoxActor& SelfActor, ABoxActor& OtherActor)
{
	if (SelfActor.GetScore() == OtherActor.GetScore() && !OtherActor.GetCompute()&& !SelfActor.GetCompute())
	{
		MCheckBoardIns->SetCanMove();
		SelfActor.SetScore();
		SelfActor.GetScore() > 100 ? SelfActor.TextCom->SetWorldSize(50) : TextCom->SetWorldSize(80);
		SelfActor.TextCom->SetText(FText::FromString(FString::FromInt(SelfActor.GetScore())));
		FVector2D tempvec = SelfActor.GetPos();
		SelfActor.GetPos() = OtherActor.GetPos();
		FVector result = FVector(SelfActor.GetPos().X * 100, SelfActor.GetPos().Y * 100, 0);
		SelfActor.SetActorLocation(OtherActor.GetActorLocation());//actor ǰ��һ��
		ManagerBoxPos.MPlaced[SelfActor.GetPos().X][SelfActor.GetPos().Y] = &SelfActor;
		SelfActor.setCompute(true);
		OtherActor.Destroy();
		ManagerBoxPos.MPlaced[tempvec.X][tempvec.Y] = nullptr;
	}
	else
	{

	}
}

void ABoxActor::MoveUp(int Maxwd, int stepy)
{
	//x�����ϣ�y�����ң��ӵ͵��߱���x����actor,�����ж�������ͨ������x�᷽��ʵ�ֵݹ���Ѱ�Ͳ���
	for (int x = 2; x > 3-Maxwd; --x)
	{
		if (ManagerBoxPos.MPlaced[x][stepy])
		{
			if (!ManagerBoxPos.MPlaced[x+1][stepy])
			{
				//ǰһ��λ��û��actor
				ManagerBoxPos.MPlaced[x][stepy]->GetPos().X += 1;
				FVector result = FVector(0.0, 0.0, 0.0);
				result.X = ManagerBoxPos.MPlaced[x][stepy]->GetPos().X * 100.0;
				result.Y = ManagerBoxPos.MPlaced[x][stepy]->GetPos().Y * 100.0;
				ManagerBoxPos.MPlaced[x][stepy]->SetActorLocation(result);//actor ǰ��һ��
				ManagerBoxPos.MPlaced[x+1][stepy] = ManagerBoxPos.MPlaced[x][stepy];//�޸������¼��actor������Ϣ
				ManagerBoxPos.MPlaced[x][stepy] = nullptr;//�ƶ�λ��֮�󣬰�ԭ��λ������Ϊfalse 
				//ManagerBoxPos.MPlaced[x - 1][y]->setCompute(true);
				MCheckBoardIns->SetCanMove();
				MoveUp(++x, stepy);
			}
			else//ǰһ��λ����actor��ִ�������߼�����
			{
				UpHitEvent(*ManagerBoxPos.MPlaced[x][stepy], *ManagerBoxPos.MPlaced[x+1][stepy]);
			}

		}
		else
		{
			continue;
		}
	}

}
void ABoxActor::MoveDown(int Maxwd, int stepy)
{
//x�����ϣ�y�����ң��ӵ͵��߱���x����actor,�����ж�������ͨ������x�᷽��ʵ�ֵݹ���Ѱ�Ͳ���
	for (int x = 1; x < Maxwd; ++x)
	{
		if (ManagerBoxPos.MPlaced[x][stepy])
		{
			if (!ManagerBoxPos.MPlaced[x - 1][stepy])
			{
				//ǰһ��λ��û��actor
				ManagerBoxPos.MPlaced[x][stepy]->GetPos().X -= 1;
				FVector result=FVector(0.0,0.0,0.0);
				result.X = ManagerBoxPos.MPlaced[x][stepy]->GetPos().X * 100.0;
				result.Y= ManagerBoxPos.MPlaced[x][stepy]->GetPos().Y * 100.0;
				ManagerBoxPos.MPlaced[x][stepy]->SetActorLocation(result);//actor ǰ��һ��
				ManagerBoxPos.MPlaced[x - 1][stepy] = ManagerBoxPos.MPlaced[x][stepy];//�޸������¼��actor������Ϣ
				ManagerBoxPos.MPlaced[x][stepy] = nullptr;//�ƶ�λ��֮�󣬰�ԭ��λ������Ϊfalse 
				//ManagerBoxPos.MPlaced[x - 1][y]->setCompute(true);
				MCheckBoardIns->SetCanMove();
				MoveDown(--x,stepy);
			}
			else//ǰһ��λ����actor��ִ�������߼�����
			{
					
				DownHitEvent(*ManagerBoxPos.MPlaced[x][stepy], *ManagerBoxPos.MPlaced[x - 1][stepy]);
				
			}
				
		}
		else
		{
			continue;
		}
	}

}
void ABoxActor::MoveLeft(int Maxwd, int stepx)
{
	//x�����ϣ�y�����ң��ӵ͵��߱���x����actor,�����ж�������ͨ������x�᷽��ʵ�ֵݹ���Ѱ�Ͳ���
	for (int y = 1; y < Maxwd; ++y)
	{
		if (ManagerBoxPos.MPlaced[stepx][y])
		{
			if (!ManagerBoxPos.MPlaced[stepx][y - 1])
			{
				//ǰһ��λ��û��actor
				ManagerBoxPos.MPlaced[stepx][y]->GetPos().Y -= 1;
				FVector result = FVector(0.0, 0.0, 0.0);
				result.X = ManagerBoxPos.MPlaced[stepx][y]->GetPos().X * 100.0;
				result.Y = ManagerBoxPos.MPlaced[stepx][y]->GetPos().Y * 100.0;
				ManagerBoxPos.MPlaced[stepx][y]->SetActorLocation(result);//actor ǰ��һ��
				ManagerBoxPos.MPlaced[stepx][y - 1] = ManagerBoxPos.MPlaced[stepx][y];//�޸������¼��actor������Ϣ
				ManagerBoxPos.MPlaced[stepx][y] = nullptr;//�ƶ�λ��֮�󣬰�ԭ��λ������Ϊfalse 
				//ManagerBoxPos.MPlaced[x - 1][y]->setCompute(true);
				MCheckBoardIns->SetCanMove();
				MoveLeft(--y, stepx);
			}
			else//ǰһ��λ����actor��ִ�������߼�����
			{

				DownHitEvent(*ManagerBoxPos.MPlaced[stepx][y], *ManagerBoxPos.MPlaced[stepx][y - 1]);
			}

		}
		else
		{
			continue;
		}
	}

}

void ABoxActor::MoveRight(int Maxwd, int stepx)
{
	//x�����ϣ�y�����ң��ӵ͵��߱���x����actor,�����ж�������ͨ������x�᷽��ʵ�ֵݹ���Ѱ�Ͳ���
	for (int y = 2; y > 3-Maxwd; --y)
	{
		if (ManagerBoxPos.MPlaced[stepx][y])
		{
			if (!ManagerBoxPos.MPlaced[stepx][y +1])
			{
				//ǰһ��λ��û��actor
				ManagerBoxPos.MPlaced[stepx][y]->GetPos().Y += 1;
				FVector result = FVector(0.0, 0.0, 0.0);
				result.X = ManagerBoxPos.MPlaced[stepx][y]->GetPos().X * 100.0;
				result.Y = ManagerBoxPos.MPlaced[stepx][y]->GetPos().Y * 100.0;
				ManagerBoxPos.MPlaced[stepx][y]->SetActorLocation(result);//actor ǰ��һ��
				ManagerBoxPos.MPlaced[stepx][y +1] = ManagerBoxPos.MPlaced[stepx][y];//�޸������¼��actor������Ϣ
				ManagerBoxPos.MPlaced[stepx][y] = nullptr;//�ƶ�λ��֮�󣬰�ԭ��λ������Ϊfalse 
				//ManagerBoxPos.MPlaced[x - 1][y]->setCompute(true);
				MCheckBoardIns->SetCanMove();
				MoveRight(++y, stepx);
			}
			else//ǰһ��λ����actor��ִ�������߼�����
			{

				DownHitEvent(*ManagerBoxPos.MPlaced[stepx][y], *ManagerBoxPos.MPlaced[stepx][y+1]);
			}

		}
		else
		{
			continue;
		}
	}

}
FVector2D ABoxActor::MakeBoxPos()
{
	    loop:
		FVector2D pos = FVector2D(FMath::RandRange(0, MCheckBoardIns->wd -1), FMath::RandRange(0, MCheckBoardIns->wd - 1));
		if (!ManagerBoxPos.MPlaced[pos.X][pos.Y])
		{
			return pos;
		}
		{
		 goto loop;
		}
}

// Sets default values
ABoxActor::ABoxActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	normalPosition = FVector2D(0, 0);
	BoxScore = 0;
	SMCube = LoadObject<UStaticMesh>(NULL, *CubePath);
	M_flower = LoadObject<UMaterial>(NULL, *MaterialsPath);

	Root_Component = CreateDefaultSubobject<USceneComponent>("Root_Component");
	SetRootComponent(Root_Component);
	SM_Component = CreateDefaultSubobject<UStaticMeshComponent>("SM_Component");
	SM_Component->AttachToComponent(Root_Component, FAttachmentTransformRules::KeepRelativeTransform);
	SM_Component->SetStaticMesh(SMCube);

	TextCom = CreateDefaultSubobject<UTextRenderComponent>("TextComponent");
	TextCom->AttachToComponent(SM_Component, FAttachmentTransformRules::KeepRelativeTransform);
	TextCom->SetRelativeTransform(FTransform(FRotator(90, 180, 0), FVector(0, 0, 51)));
	TextCom->SetWorldSize(80);
	TextCom->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	TextCom->VerticalAlignment = EVerticalTextAligment::EVRTA_TextCenter;
	TextCom->TextRenderColor = FColor(0, 0, 0, 0);
	TextCom->SetText(FText::FromString("2"));


	if (M_flower)
	{
	 SMCube->SetMaterial(0,M_flower);
	}

	

}

// Called when the game starts or when spawned
void ABoxActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoxActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//class ACheckerBoardActor





