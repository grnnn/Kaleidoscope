// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "Kaleidoscope.h"
#include "KaleidoscopeCharacter.h"
#include "MyHUD.h"

//////////////////////////////////////////////////////////////////////////
// AMyProject6Character

AKaleidoscopeCharacter::AKaleidoscopeCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{


	
	walkStep = 0;
	canTurnBool = false;
	canWalkBool = false;
	canJogBool = false;
	cppDevelopmentTool = false;

	

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FollowCamera"));
	FollowCamera->AttachTo(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm


	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AKaleidoscopeCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{

	// Set up gameplay key bindings
	check(InputComponent);

	if (cppDevelopmentTool){
		canTurnBool = true;
		canWalkBool = true;
		canJogBool = true;
	}
		

	
	//InputComponent->BindAction("EKey", IE_Pressed, this, &AMyProject6Character::TriggerNewCameraOn);
	//InputComponent->BindAction("EKey", IE_Released, this, &AMyProject6Character::TriggerNewCameraOff);

	//InputComponent->BindAction("FKey", IE_Pressed, this, &AMyProject6Character::TriggerNewCameraOnF);
	//InputComponent->BindAction("FKey", IE_Released, this, &AMyProject6Character::TriggerNewCameraOffF);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	InputComponent->BindAxis("MoveForward", this, &AKaleidoscopeCharacter::walkingControl);
	InputComponent->BindAxis("MoveRight", this, &AKaleidoscopeCharacter::turningControl);
	//InputComponent->BindAxis("MoveRight", this, &APawn::AddControllerYawInput);
	//InputComponent->BindAxis("MoveRight", this, &AMyProject6Character::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &AKaleidoscopeCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &AKaleidoscopeCharacter::LookUpAtRate);

	// handle touch devices
	InputComponent->BindTouch(IE_Pressed, this, &AKaleidoscopeCharacter::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &AKaleidoscopeCharacter::TouchStopped);

}


void AKaleidoscopeCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	// jump, but only on the first touch
	if (FingerIndex == ETouchIndex::Touch1)
	{
		Jump();
	}
}

void AKaleidoscopeCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (FingerIndex == ETouchIndex::Touch1)
	{
		StopJumping();
	}
}

void AKaleidoscopeCharacter::TurnAtRate(float Rate)
{
	
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AKaleidoscopeCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AKaleidoscopeCharacter::MoveRight(float Value)
{
	
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}


/*
void  AMyProject6Character::TriggerNewCameraOn()
{
	APlayerController* MyPC = Cast<APlayerController>(Controller);
	if (MyPC)
	{
		AHUD *ahud = MyPC->GetHUD();
		MyHud = Cast<AMyHUD>(ahud);
	}
	if (MyHud)
	{
		MyHud->setIsTrigger(true);
	}

}
*/

/*
void  AMyProject6Character::TriggerNewCameraOff()
{
	
}
*/



/* ============== AKaleidoscopeCharacter::walkingControl ======================================
If canTurn boolean is fasle, player can not walk
Pre:  Rate: the walking speed which is set in project setting, recieveing from user input (W key)
Post: Character walks if bool is true

*/
void AKaleidoscopeCharacter::walkingControl(float Value)
{
	// full running speed is used as a development tool
	if (Value == 1.0f || cppDevelopmentTool)
		this->MoveForward(Value);

	if (!canWalkBool)
		return;

	// jogging value is defined in project setting, current value is 0.55 (05/29/2015)
	// if the value is greater than 0.3 (walking speed) but jogging is not allowed yet, return nothing
	if (!canJogBool && Value > 0.3f)
		return;
	
	if (Value == 0.3f || Value == 0.55f || Value <= 0)
		this->MoveForward(Value);
}

void AKaleidoscopeCharacter::MoveForward(float Value)
{
	// for controller
	if (Value < 0 && canJogBool)
	{
		Value = 0.55f;
		
	}
	else if (Value < 0)
	{
		//Value = 0.55f;
		return;
	}

	if ((Controller != NULL) && (Value != 0.0f))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, FString::Printf(TEXT("CCC")));
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		
		AddMovementInput(Direction, Value);
		increaseWalkStep();
	}
}


void AKaleidoscopeCharacter::increaseWalkStep()
{
	walkStep++;
	APlayerController* MyPC = Cast<APlayerController>(Controller);
	if (MyPC)
	{
		AHUD *ahud = MyPC->GetHUD();
		MyHud = Cast<AMyHUD>(ahud);
	}
	if (MyHud)
	{
		int w = (int)walkStep;
		MyHud->setWalkStep(walkStep);
	}
}


/* ============== AKaleidoscopeCharacter::turningControl ======================================
If canTurn boolean is fasle, player can not turn
Pre:  Rate: the turning speed which is set in project setting, recieveing from user input (A/D key)
Post: Character turns if bool is true

*/

void AKaleidoscopeCharacter::turningControl(float Rate)
{
	if (!canTurnBool)
		return;
	else
		// same as TurningAtRate function
		AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}