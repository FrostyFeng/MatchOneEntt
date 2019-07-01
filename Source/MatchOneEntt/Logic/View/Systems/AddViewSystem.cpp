#include "AddViewSystem.h"
#include "Components/AssetComponent.h"
#include "Components/ViewComponent.h"
#include "Components/WorldComponent.h"
#include "Components/AssetLibraryComponent.h"
#include "Components/ViewContainerComponent.h"
#include "PaperSpriteComponent.h"
#include "Game/Actors/GamePiece.h"
#include "Game/Actors/ViewContainer.h"
#include "Data/AssetLibrary.h"

void AddViewSystem::Update(entt::registry& Registry)
{
    auto View = Registry.view<AssetComponent>();

    if (View.size() > 0)
    {
        auto& World = Registry.ctx<WorldComponent>();
        auto& ViewContainer = Registry.ctx<ViewContainerComponent>();
        auto& AssetLibrary = Registry.ctx<AssetLibraryComponent>();

        for (auto Entity : View)
        {
            auto& Asset = View.get(Entity);
            auto GamePieceClass = AssetLibrary.Value->GamePieces.FindRef(Asset.Value);

            auto actor = World.Value->SpawnActor<AGamePiece>(GamePieceClass, FVector::ZeroVector, FRotator::ZeroRotator);
            actor->AttachToActor(ViewContainer.Value, FAttachmentTransformRules::KeepRelativeTransform);

            auto renderComponent = actor->GetRenderComponent();
            renderComponent->SetMobility(EComponentMobility::Movable);

            Registry.assign<ViewComponent>(Entity, actor);
            Registry.remove<AssetComponent>(Entity);
        }
    }
}
