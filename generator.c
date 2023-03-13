#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

#include "MyActor.generated.h"

UCLASS()
class MYGAME_API AMyActor : public AActor
{
    GENERATED_BODY()

public:
    AMyActor();

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* MeshComponent;

    UPROPERTY(VisibleAnywhere)
    USphereComponent* SphereComponent;

    UPROPERTY(EditAnywhere, Category = "Gameplay")
    int32 Score = 0;

    UPROPERTY(EditAnywhere, Category = "Gameplay")
    int32 ScoreToWin = 10;

    UPROPERTY(EditAnywhere, Category = "Gameplay")
    UParticleSystem* ExplosionEffect;

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnSphereOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    void EndGame(bool bWin);

private:
    bool bGameOver = false;
};

