#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"                    //Struct FInputActionInstance (enhanced input system)
#include "NBPlayerCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
//Forward Declarations
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class NUCLEARBOOGALOO_API ANBPlayerCharacter : public ACharacter
{
	GENERATED_BODY()


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<USpringArmComponent> SpringArmComp;	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> CameraComp;

	//Enhanced Input System: InputMappingContext
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	TObjectPtr<UInputMappingContext> DefaultInputMappingContext;

	//Enhanced Input System: InputActions
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput|InputActions")
	TObjectPtr<UInputAction>  Input_Move;
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput|InputActions")
	TObjectPtr<UInputAction>  Input_Interact;
	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput|InputActions")
	TObjectPtr<UInputAction>  Input_LookMouse;	

	void Move(const FInputActionInstance& Instance);
	void LookMouse(const FInputActionValue& InputValue);
	void PrimaryInteract();



	
	
public:
	ANBPlayerCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
protected:
	virtual void BeginPlay() override;



};
