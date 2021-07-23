// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString(TEXT("Welcome to Steam Audio Test")));
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FQuat QuatRotation;
	FVector NewLocation;
	FVector CurrentScale;
	switch (Mode)
	{
	case 0: //Viewer mode
		if (!MovementDirection.IsZero())
		{
			NewLocation = GetActorLocation() + (MovementDirection * DeltaTime * MovementSpeed);
			AddActorLocalOffset((MovementDirection * DeltaTime * MovementSpeed));
		}
		QuatRotation = FQuat(FRotator(Pitch, Yaw, 0.0f));
		AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
		break;
	case 1: //Scale mode
		CurrentScale = Chamber->GetActorScale3D();
		switch (Axis)
		{
		case 0:
			Chamber->SetActorScale3D(CurrentScale + FVector(MovementDirection.X * ScaleSpeed, 0, 0));
			break;
		case 1:
			Chamber->SetActorScale3D(CurrentScale + FVector(0, MovementDirection.X * ScaleSpeed, 0));
			break;
		case 2:
			Chamber->SetActorScale3D(CurrentScale + FVector(0, 0, MovementDirection.X * ScaleSpeed));
			break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("No Axis selected"));
		}
		break;
	case 2: //Boombox mode
		switch (Axis)
		{
		case 0:
			Boombox->SetActorLocation(Boombox->GetActorLocation() + FVector(MovementDirection.X * BoomboxSpeed, 0, 0));
			break;
		case 1:
			Boombox->SetActorLocation(Boombox->GetActorLocation() + FVector(0, MovementDirection.X * BoomboxSpeed, 0));		
			break;
		case 2:
			Boombox->SetActorLocation(Boombox->GetActorLocation() + FVector(0, 0, MovementDirection.X * BoomboxSpeed));			
			break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("No Axis is selected"));
		}
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Unknown case in Tick Switch"));
	}
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAction("ToggleMode", IE_Pressed, this, &AMyPawn::ToggleMode);
	InputComponent->BindAction("ToggleAxis", IE_Pressed, this, &AMyPawn::ToggleAxis);
	InputComponent->BindAxis("MoveForward", this, &AMyPawn::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMyPawn::MoveRight);
	InputComponent->BindAxis("Rotate", this, &AMyPawn::Move_XAxis);
	InputComponent->BindAxis("Lookup", this, &AMyPawn::Move_YAxis);

}

void AMyPawn::Move_XAxis(float AxisValue)
{
	Yaw = AxisValue;
}

void AMyPawn::Move_YAxis(float AxisValue)
{
	Pitch = AxisValue;
}

void AMyPawn::MoveForward(float AxisValue)
{
	
	MovementDirection.X = FMath::Clamp(AxisValue, -1.0f, 1.0f);
}

void AMyPawn::MoveRight(float AxisValue)
{
	MovementDirection.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f);	
}

void AMyPawn::ToggleMode() 
{
	
	switch (Mode)
	{
	case 0:
		UE_LOG(LogTemp, Warning, TEXT("Switching to Scale Mode"));//Scale mode
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString(TEXT("Scale Mode Enabled")));
		Mode++;
		break;
	case 1:
		UE_LOG(LogTemp, Warning, TEXT("Switching to Boombox Mode"));//Boombox mode
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString(TEXT("Boombox Mode Enabled")));
		Mode++;
		break;
	case 2:
		UE_LOG(LogTemp, Warning, TEXT("Switching to Viewer Mode"));//Viewer mode
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString(TEXT("Viewer Mode Enabled")));
		Mode = 0;
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Unknown case in Toggle Mode switch"));
	}
	
}

void AMyPawn::ToggleAxis()
{	
	switch (Axis)
	{
	case 0:
		UE_LOG(LogTemp, Warning, TEXT("Selecting Y Axis "));//Y Axis
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString(TEXT("Y Axis selected")));
		Axis++;
		break;
	case 1:
		UE_LOG(LogTemp, Warning, TEXT("Selecting Z Axis"));//Z Axis
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString(TEXT("Z Axis selected")));
		Axis++;
		break;
	case 2:
		UE_LOG(LogTemp, Warning, TEXT("Selecting X Axis"));//X Axis
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString(TEXT("X Axis selected")));
		Axis = 0;
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Unknown case in Toggle Axis switch"));
	}

}



