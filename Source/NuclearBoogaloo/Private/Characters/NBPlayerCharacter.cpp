#include "NuclearBoogaloo/Public/Characters/NBPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "NuclearBoogaloo/Public/Controllers/NBPlayerController.h" //PlayerController.h file
//Enhanced Input System
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h" //Used with GetCharacterMovement()


ANBPlayerCharacter::ANBPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp -> SetupAttachment(GetRootComponent());

	SpringArmComp -> bUsePawnControlRotation = true;
	SpringArmComp -> SetUsingAbsoluteRotation(true); 	//Needed if setting bOrientRotationToMovement set to true. Enabling for now
	
	CameraComp= CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComp ->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	
	bUseControllerRotationYaw = false; //set it to true to get the hand to always face in the direction of the camera

	GetCharacterMovement() -> bOrientRotationToMovement = true;
}



void ANBPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}


void ANBPlayerCharacter::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
	
}


void ANBPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent); //Call base functionality


	//Adding Mapping Input Context
	const TObjectPtr<APlayerController> PC = GetController<APlayerController>();
	const TObjectPtr<ULocalPlayer> LP = PC -> GetLocalPlayer();

	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> Subsystem = LP -> GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem); // assert to make sure this is valid

	Subsystem -> ClearAllMappings(); //Start fresh. If respawning and still have old mappings set, clear them out

	//Add Mappings for this game. For now, only need one Mapping Context (simple prototype game)
	Subsystem -> AddMappingContext(DefaultInputMappingContext, 0);

	//New Enhanced Input System
	TObjectPtr<UEnhancedInputComponent> InputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	//Performing Bindings to InputActions
	InputComp -> BindAction(Input_Move, ETriggerEvent::Triggered, this, &ANBPlayerCharacter::Move);
	InputComp -> BindAction(Input_Interact, ETriggerEvent::Triggered, this, &ANBPlayerCharacter::PrimaryInteract);
	InputComp -> BindAction(Input_LookMouse, ETriggerEvent::Triggered, this, &ANBPlayerCharacter::LookMouse);
	
	
}

void ANBPlayerCharacter::Move(const FInputActionInstance& Instance)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	
	const FVector2D AxisValue = Instance.GetValue().Get<FVector2D>();					// Get value from input (combined value from WASD keys or single Gamepad stick) and convert to Vector (x,y)
	AddMovementInput(ControlRot.Vector(), AxisValue.Y); 					// Move forward/back
	
	const FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y); 	
	AddMovementInput(RightVector, AxisValue.X);											// Move Right/Left strafe
}
void ANBPlayerCharacter::LookMouse(const FInputActionValue& InputValue)
{
	const FVector2D Value = InputValue.Get<FVector2D>();
	AddControllerYawInput(Value.X);
	AddControllerPitchInput(Value.Y);
}
void ANBPlayerCharacter::PrimaryInteract()
{
	
}


