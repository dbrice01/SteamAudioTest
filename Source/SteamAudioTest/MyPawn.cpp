// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
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
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!isScaleMode)
	{
		if (!isBoomboxMode) // Walking around
		{
			if (!MovementDirection.IsZero())
			{
				const FVector NewLocation = GetActorLocation() + (MovementDirection * DeltaTime * MovementSpeed);
				AddActorLocalOffset((MovementDirection * DeltaTime * MovementSpeed));
			}
			FQuat QuatRotation = FQuat(FRotator(Pitch, Yaw, 0.0f));
			AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
		}
		else //Boombox Mode
		{
			if (isXAxis)
			{
				Boombox->SetActorLocation(Boombox->GetActorLocation() + FVector(MovementDirection.X * BoomboxSpeed, 0, 0));
			}
			else if (isYAxis)
			{
				Boombox->SetActorLocation(Boombox->GetActorLocation() + FVector(0, MovementDirection.X * BoomboxSpeed, 0));
			}
			else if (isZAxis)
			{
				Boombox->SetActorLocation(Boombox->GetActorLocation() + FVector(0, 0, MovementDirection.X * BoomboxSpeed));
			}
		}
	}
	else //Scale Mode
	{
		FVector CurrentScale = Chamber->GetActorScale3D();
		if (isXAxis)
		{
			Chamber->SetActorScale3D(CurrentScale + FVector(MovementDirection.X * ScaleSpeed , 0, 0));
		}
		else if (isYAxis)
		{
			Chamber->SetActorScale3D(CurrentScale + FVector( 0, MovementDirection.X * ScaleSpeed, 0));
		}
		else if (isZAxis)
		{
			Chamber->SetActorScale3D(CurrentScale + FVector(0, 0, MovementDirection.X * ScaleSpeed));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("In Scale Mode, no axis selected"));
		}
	}


	
	//UE_LOG(LogTemp, Warning, TEXT("Pawn Rotation is %s"), *GetActorRotation().ToString());

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAction("ScaleMode", IE_Pressed, this, &AMyPawn::ScaleModeStart);
	InputComponent->BindAction("ScaleMode", IE_Released, this, &AMyPawn::ScaleModeStop);
	InputComponent->BindAction("BoomboxMode", IE_Pressed, this, &AMyPawn::BoomboxModeStart);
	InputComponent->BindAction("BoomboxMode", IE_Released, this, &AMyPawn::BoomboxModeStop);
	InputComponent->BindAction("isXAxis", IE_Pressed, this, &AMyPawn::XAxisStart);
	InputComponent->BindAction("isXAxis", IE_Released, this, &AMyPawn::XAxisStop);
	InputComponent->BindAction("isYAxis", IE_Pressed, this, &AMyPawn::YAxisStart);
	InputComponent->BindAction("isYAxis", IE_Released, this, &AMyPawn::YAxisStop);
	InputComponent->BindAction("isZAxis", IE_Pressed, this, &AMyPawn::ZAxisStart);
	InputComponent->BindAction("isZAxis", IE_Released, this, &AMyPawn::ZAxisStop);

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

void AMyPawn::ScaleModeStart()
{
	isScaleMode = true;
	UE_LOG(LogTemp, Warning, TEXT("Starting ScaleMode"));
}

void AMyPawn::ScaleModeStop()
{
	isScaleMode = false;
	UE_LOG(LogTemp, Warning, TEXT("Stopping ScaleMode"));
}

void AMyPawn::BoomboxModeStart()
{
	isBoomboxMode = true;
	UE_LOG(LogTemp, Warning, TEXT("Starting BoomboxMode"));
}

void AMyPawn::BoomboxModeStop()
{
	isBoomboxMode = false;
	UE_LOG(LogTemp, Warning, TEXT("Stopping BoomboxMode"));
}

void AMyPawn::XAxisStart()
{
	isXAxis = true;
	UE_LOG(LogTemp, Warning, TEXT("Stopping isXAxis"));
}

void AMyPawn::XAxisStop()
{
	isXAxis = false;
	UE_LOG(LogTemp, Warning, TEXT("Starting isXAxis"));
}

void AMyPawn::YAxisStart()
{
	isYAxis = true;
	UE_LOG(LogTemp, Warning, TEXT("Stopping isYAxis"));
}

void AMyPawn::YAxisStop()
{
	isYAxis = false;
	UE_LOG(LogTemp, Warning, TEXT("Stopping isYAxis"));
}

void AMyPawn::ZAxisStart()
{
	isZAxis = true;
	UE_LOG(LogTemp, Warning, TEXT("Starting isZAxis"));
}

void AMyPawn::ZAxisStop()
{
	isZAxis = false;
	UE_LOG(LogTemp, Warning, TEXT("Stopping isZAxis"));
}


