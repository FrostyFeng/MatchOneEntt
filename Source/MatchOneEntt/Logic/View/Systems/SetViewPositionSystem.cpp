#include "SetViewPositionSystem.h"
#include "Components/ViewComponent.h"
#include "Components/AddViewComponent.h"
#include "Components/PositionComponent.h"

void SetViewPositionSystem::Initialize(entt::registry& Registry) {}

void SetViewPositionSystem::Update(entt::registry& Registry)
{
    auto View = Registry.view<AddViewComponent, PositionComponent, ViewComponent>();

    for (auto Entity : View)
    {
        auto& Position = View.get<PositionComponent>(Entity);
        auto& ViewComp = View.get<ViewComponent>(Entity);

        auto X = 0.0f;
        auto Y = Position.Value.X * 125.0f;
        auto Z = Position.Value.Y * 125.0f;

        ViewComp.Value->SetActorLocationAndRotation(FVector(X, Y, Z), FQuat(FRotator(0.0f, 90.0f, 0.0f)));

        Registry.remove<AddViewComponent>(Entity);
    }
}
