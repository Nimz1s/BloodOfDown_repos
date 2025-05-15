#include "BTTask_FindPatrolPoint.h"
#include "NPC.h"
#include "NPC_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindPatrolPoint::UBTTask_FindPatrolPoint(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Find Patrol Point");

}
EBTNodeResult::Type UBTTask_FindPatrolPoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	// attempt to get the NPC's controller
	if (auto* const cont = Cast<ANPC_AIController>(OwnerComp.GetAIOwner()))
	{
		// attempt to get the blackboard component from the behaviour tree
		if (auto* const bc = OwnerComp.GetBlackboardComponent())
		{

			// get the current patrol path index from the blackboard
			auto const Index = bc->GetValueAsInt(GetSelectedBlackboardKey());
			// get the NPC
				if (auto* npc = Cast<ANPC>(cont->GetPawn()))
				{
					// get the current patrol path vector from the NPC - this is local to the patrol path actor
					auto const Point = npc->GetPatrolPath()->GetPatrolPoint(Index);
					// convert the local vector to a global point
					auto const GlobalPoint = npc->GetPatrolPath()->GetActorTransform().TransformPosition(Point);
					bc->SetValueAsVector(PatrolPathVectorKey.SelectedKeyName, GlobalPoint);
					FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
					return EBTNodeResult::Succeeded;
				}
		}
	}
	return EBTNodeResult::Failed;
}