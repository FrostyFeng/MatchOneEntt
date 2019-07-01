#include "GameBoardSystem.h"
#include "Logic/GameBoard/GameBoardLogic.h"
#include "Components/GameBoardComponent.h"
#include "Components/GameBoardUpdateComponent.h"
#include "Components/GameBoardElementComponent.h"
#include "Components/PositionComponent.h"
#include "Components/DestroyedComponent.h"
#include "Components/FillEventComponent.h"
#include "Components/FallEventComponent.h"

void GameBoardSystem::Initialize(entt::registry& Registry)
{
    Registry.set<GameBoardComponent>(8, 9);

    auto& GameBoard = Registry.ctx<GameBoardComponent>();

    for (int row = 0; row < GameBoard.Rows; row++)
    {
        for (int column = 0; column < GameBoard.Columns; column++)
        {
            float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

            if (r > 0.91f)
            {
                GameBoardLogic::CreateBlocker(Registry, column, row);
            }
            else
            {
                GameBoardLogic::CreateRandomPiece(Registry, column, row);
            }
        }
    }

    Registry.create<GameBoardUpdateComponent>();
}

void GameBoardSystem::Update(entt::registry& Registry)
{
    auto GameBoardUpdateView = Registry.view<GameBoardUpdateComponent>();

    if (GameBoardUpdateView.size() > 0)
    {
        auto& GameBoard = Registry.ctx<GameBoardComponent>();

        for (auto GameBoardUpdateEntity : GameBoardUpdateView)
        {
            auto ElementView = Registry.view<GameBoardElementComponent, PositionComponent>();

            for (auto Entity : ElementView)
            {
                auto Position = ElementView.get<PositionComponent>(Entity);

                if (int(Position.Value.X) >= GameBoard.Columns || int(Position.Value.Y) >= GameBoard.Rows)
                {
                    Registry.assign<DestroyedComponent>(Entity);
                }
            }

            Registry.destroy(GameBoardUpdateEntity);
        }
    }
}
