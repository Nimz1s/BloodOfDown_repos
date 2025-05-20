// Fill out your copyright notice in the Description page of Project Settings.


#include "CppAICharacterBase.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"

#include "CoreMinimal.h" // Include CoreMinimal.h to ensure FVector is available  
#include <HealthBarWidget.h>
#include <NPC.h>
#include <BloodOfDown/BloodOfDownCharacter.h>

namespace defs
{
	FVector const HealthBarZ{ 0.f, 0.f, 95.f }; // Z offset for health bar  
	/*FVector const RightFirstBoxSize{ 5.f };*/
	FName const RightFirstSocketName{"hand_r_socket"}; // Z offset for health bar
	FVector const CollisionBoxLocation{ -7.f, 0.f, 0.f }; 
}	

// Sets default values
ACppAICharacterBase::ACppAICharacterBase() : WidgetComponent{ CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthValue")) }, Health{MaxHealth}, 
	RightFirstCollisionBox{ CreateDefaultSubobject<UBoxComponent>(TEXT("RightFirstCollisionBox")) }
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (WidgetComponent)
	{
		WidgetComponent->SetupAttachment(RootComponent);
		WidgetComponent->SetWidgetSpace (EWidgetSpace::Screen);
		WidgetComponent->SetRelativeLocation(defs::HealthBarZ);
		static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass{ TEXT("/Game/AI/UI/BP_HealthBarEnemy") };
		if (WidgetClass.Succeeded())
		{
			WidgetComponent->SetWidgetClass((WidgetClass.Class));
		}	
	}

	if (RightFirstCollisionBox)
	{
		FAttachmentTransformRules const Rules{
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::KeepWorld,
			false };
		RightFirstCollisionBox->AttachToComponent(GetMesh(), Rules, defs::RightFirstSocketName);
		RightFirstCollisionBox->SetRelativeLocation(defs::CollisionBoxLocation);

		// ✳️ Вимикаємо колізію на старті
		UE_LOG(LogTemp, Warning, TEXT("Attack End - Collision Disabled"));
		RightFirstCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		RightFirstCollisionBox->SetNotifyRigidBodyCollision(false);
	}
	
}
// Called when the game starts or when spawned
void ACppAICharacterBase::BeginPlay()
{
	Super::BeginPlay();
	RightFirstCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ACppAICharacterBase::OnAttackOverlapBegin);
	RightFirstCollisionBox->OnComponentEndOverlap.AddDynamic(this, &ACppAICharacterBase::OnAttackOverlapEnd);

	RightFirstCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightFirstCollisionBox->SetNotifyRigidBodyCollision(false);  // якщо не використовуєш фізику — можеш не ставити
	RightFirstCollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	RightFirstCollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);  // тільки Pawn
	
}


void ACppAICharacterBase::OnAttackOverlapBegin(UPrimitiveComponent* const OverlappedComponent, AActor* const OtherActor, UPrimitiveComponent* const OtherComponent, int const OtherBodyIndex, bool const FromSweep, FHitResult const& SweepResult)
{
	if (OtherActor == this)
	{
		return;
	}
	else if (auto const Enemy = Cast<ANPC>(OtherActor))
	{
		auto const NewHealth = Enemy->GetHealth() - Enemy->GetMaxHealth() * 0.1f;
		Enemy->SetHealth(NewHealth);
	}		
	else if (auto const Player = Cast<ABloodOfDownCharacter>(OtherActor))
	{
		auto const NewHealth = Player->GetHealth() - Player->GetMaxHealth() * 0.07f;
		Player->SetHealth(NewHealth);
	}
		
}
void ACppAICharacterBase::OnAttackOverlapEnd(UPrimitiveComponent* const OverlappedComponent, AActor* const OtherActor, UPrimitiveComponent* OtherComponent, int const OtherBodyIndex)
{
}


// Called every frame
void ACppAICharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (auto const widget = Cast<UHealthBarWidget>(WidgetComponent->GetUserWidgetObject()))
	{
		widget->SetBarValuePercent(Health / MaxHealth);
	}
		

}
// Called to bind functionality to input
void ACppAICharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


float ACppAICharacterBase::GetHealth() const
{
	return Health;
}

float ACppAICharacterBase::GetMaxHealth() const
{
	return MaxHealth;
}

void ACppAICharacterBase::SetHealth(float const NewHealth)
{
	Health = NewHealth;
	if (Cast<ABloodOfDownCharacter>(this))
	{
		if (Health <= 0)
		{
			UE_LOG(LogTemp, Error, TEXT("You Lose!!!!"));
			GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
		}
	}
	else if (Cast<ANPC>(this))
	{
		if (Health <= 0)
		{
			UE_LOG(LogTemp, Error, TEXT("You Win!!!!"));
			GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
		}
			
	}
				
}

void ACppAICharacterBase::AttackStart()
{
	/*UE_LOG(LogTemp, Warning, TEXT("Attack Start - Collision Enabled"));
	RightFirstCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	RightFirstCollisionBox->SetNotifyRigidBodyCollision(true);*/

	UE_LOG(LogTemp, Warning, TEXT("Attack Start - Collision Enabled"));
	RightFirstCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ACppAICharacterBase::AttackEnd()
{
	/*UE_LOG(LogTemp, Warning, TEXT("Attack End - Collision Disabled"));
	RightFirstCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightFirstCollisionBox->SetNotifyRigidBodyCollision(false);*/

	UE_LOG(LogTemp, Warning, TEXT("Attack End - Collision Disabled"));
	RightFirstCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

