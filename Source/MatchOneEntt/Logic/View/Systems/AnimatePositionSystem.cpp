#include "AnimatePositionSystem.h"
#include "Components/PositionUpdatedComponent.h"
#include "Components/PositionComponent.h"
#include "Components/ViewComponent.h"
#include "Components/GameBoardComponent.h"

void AnimatePositionSystem::Initialize(entt::registry& Registry) {}

void AnimatePositionSystem::Update(entt::registry& Registry)
{
    auto View = Registry.view<PositionUpdatedComponent, PositionComponent, ViewComponent>();

    if (View.size() > 0)
    {
        auto& GameBoard = Registry.ctx<GameBoardComponent>();

        for (auto Entity : View)
        {
            auto& Position = View.get<PositionComponent>(Entity);
            auto& ViewComp = View.get<ViewComponent>(Entity);

            auto IsTopRow = Position.Value.Y == GameBoard.Rows - 1;

            auto X = 0.0f;
            auto Y = Position.Value.X * 125.0f;
            auto Z = Position.Value.Y * 125.0f;

            if (IsTopRow)
            {
                ViewComp.Value->SetActorLocation(FVector(X, Y, Z + 1));
            }

            ViewComp.Value->SetActorLocation(FVector(X, Y, Z));

            Registry.remove<PositionUpdatedComponent>(Entity);
        }
    }
}
