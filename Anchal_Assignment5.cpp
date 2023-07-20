// Please note that this code is just an example and may require modifications to fit your specific game design.

// Import the necessary libraries and classes
import Engine from 'UnrealEngine';
import Assets from 'UnrealAssets';

class MobileGameAssignment : GameModeBase
{
    UPROPERTY(EditAnywhere)
    USoundBase* BackgroundSoundtrack;
    
    UPROPERTY(EditAnywhere)
    USoundBase* BubblePoppingSound;
    
    UPROPERTY(EditAnywhere)
    USoundBase* SplatSound;
    
    UPROPERTY(EditAnywhere)
    UMaterial* BrandColorMaterial;
    
    UPROPERTY(EditAnywhere)
    UTexture2D* GCLogoTexture;
    
    UPROPERTY(EditAnywhere)
    UStaticMesh* CustomObjectMesh;
    
    UPROPERTY(EditAnywhere)
    UParticleSystem* ExplosionParticle;
    
    UPROPERTY(EditAnywhere)
    UStaticMeshComponent* GunMesh;
    
    UPROPERTY(EditAnywhere)
    UMaterialInterface* BrandColorMaterial;
    
    UPROPERTY(EditAnywhere)
    UStaticMeshComponent* CubeMesh;
    
    UPROPERTY(EditAnywhere)
    UTextRenderComponent* NameLabel;
    
    UFUNCTION(BlueprintOverride)
    void BeginPlay()
    {
        Super.BeginPlay();
        
        // Play the background soundtrack
        PlaySound(BackgroundSoundtrack);
        
        // Change the gun shot sound to bubble popping noise
        GunMesh->OnFireSound = BubblePoppingSound;
        
        // Set up the collision event for the cube mesh
        CubeMesh->OnComponentHit.AddDynamic(this, &MobileGameAssignment::OnCubeHit);
        
        // Change the arena's colors to GC brand colors
        ArenaMaterialInstance->SetVectorParameterValue("Color", GCBrandColor);
        
        // Add a text label to the floor of the arena showing your name and course code
        NameLabel->SetText(FText::FromString("Your Name - Course Code"));
        
        // Place the GC logo as a picture on the back wall
        UMaterialInstanceDynamic* LogoMaterialInstance = UMaterialInstanceDynamic::Create(BrandColorMaterial, nullptr);
        LogoMaterialInstance->SetTextureParameterValue("Texture", GCLogoTexture);
        BackWallMesh->SetMaterial(0, LogoMaterialInstance);
        
        // Add a 3D object of your choice to the arena
        UStaticMeshComponent* CustomObject = NewObject<UStaticMeshComponent>(this);
        CustomObject->SetStaticMesh(CustomObjectMesh);
        CustomObject->AttachToComponent(ArenaMesh, FAttachmentTransformRules::KeepRelativeTransform);
        
        // Set the gun to fire continuously when shooting, automatic machine gun style
        GunMesh->FireRate = 0.1f;
        
        // Change the default UE application icon to one of your choice
        UTexture2D* NewIcon = LoadTextureFromAsset("/Game/Textures/CustomIcon");
        UGameplayStatics::SetGameInstance(GetWorld(), NewIcon);
        
        // Comment your code - add comments throughout your blueprint or code to explain its functionality
        
        // Provide attributions to assets used - create a text file or add comments listing the asset sources
        
        // Package for Android OR iOS - use Unreal Engine's packaging tools to generate the APK/IPA file
        
        // Deliver both source and packaged game - include the project files and the packaged file in your submission
    }
    
    UFUNCTION()
    void OnCubeHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
    {
        // Make the cube disappear in an explosion when hit
        CubeMesh->SetVisibility(false);
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticle, CubeMesh->GetComponentLocation());
        
        // Play the splat sound
        PlaySoundAtLocation(SplatSound, Hit.ImpactPoint);
    }
}
