class ZenTirednessAgent: AgentBase
{
    static int MAX_COUNT = 1000;

    override void Init()
    {
        m_Type                  = CHFSleep_Agents.TIREDNESS;
        m_Invasibility          = 0.08;
        m_TransferabilityIn     = 0;
        m_TransferabilityOut    = 0;
        m_AntibioticsResistance = 1;
        m_MaxCount              = MAX_COUNT;
        m_Potency               = EStatLevels.GREAT;
        m_DieOffSpeed           = 1;
    }

    override float GetInvasibilityEx(PlayerBase player)
    {
        if (!player || player.IsPlayerSleeping() || !player.IsAlive())
            return 0;

        if (GetCHFSleepConfig().MaxWakeTime > 0)
        {
            m_Invasibility = (float)m_MaxCount / (GetCHFSleepConfig().MaxWakeTime * 60);

            if (!GetCHFSleepConfig().EnableMovementPenalties)
                return m_Invasibility;
        }

        float modifier = 1.0;

        if (!player.m_MovementState)
            return m_Invasibility;

        // No penalty for walking or crouch-walking (or any other behaviour - todo, add more behaviours? Or is this enough to cover most bases?)

        if (player.IsSwimming()) // Swimming
        {
            if (player.m_MovementState.m_iMovement == DayZPlayerConstants.MOVEMENTIDX_SPRINT) // Swimming fast
            {
                modifier = GetCHFSleepConfig().SwimFastPenalty;
            }
            else
            if (player.m_MovementState.m_iMovement == DayZPlayerConstants.MOVEMENTIDX_RUN) // Swimming slow
            {
                modifier = GetCHFSleepConfig().SwimSlowPenalty;
            }
        } else
        if (player.IsClimbingLadder()) // Climbing ladder
        {
            if (player.m_MovementState.m_iMovement == DayZPlayerConstants.MOVEMENTIDX_RUN) // Climbing fast
            {
                modifier = GetCHFSleepConfig().ClimbFastPenalty;
            }
            else
            if (player.m_MovementState.m_iMovement == DayZPlayerConstants.MOVEMENTIDX_WALK) // Climbing slow
            {
                modifier = GetCHFSleepConfig().ClimbSlowPenalty;
            }
        } else
        if (player.m_MovementState.m_iMovement == DayZPlayerConstants.MOVEMENTIDX_SPRINT) // Sprinting
        {
            if (player.m_MovementState.m_iStanceIdx == DayZPlayerConstants.STANCEIDX_ERECT) // While erect IF YOU KNOW WHAT I MEAN WINK WINK
            {
                modifier = GetCHFSleepConfig().SprintUprightPenalty;
            }
            else if (player.m_MovementState.m_iStanceIdx == DayZPlayerConstants.STANCEIDX_CROUCH) // While crouched
            {
                modifier = GetCHFSleepConfig().SprintCrouchedPenalty;
            }
        }
        else
        if (player.m_MovementState.m_iMovement == DayZPlayerConstants.MOVEMENTIDX_RUN) // Jogging
        {
            modifier = GetCHFSleepConfig().JoggingPenalty;
        }
        else
        if (player.m_MovementState.m_iMovement == DayZPlayerConstants.MOVEMENTIDX_WALK) // Walking
        {
            // With heavy item in hands
            ItemBase item = ItemBase.Cast(player.GetItemInHands());
            if (item)
            {
                if (item.IsHeavyBehaviour())
                {
                    modifier = GetCHFSleepConfig().WalkingHeavyItemPenalty;
                }
            }
        }

        //player.ZS_SendMessage("Current Movement State=" + player.m_MovementState.m_iMovement + " / StanceIndex=" + player.m_MovementState.m_iStanceIdx + " - invasibility=" + (m_Invasibility * modifier) + " (Swimming=" + player.IsSwimming() + ", Climbing=" + player.IsClimbingLadder() + ")");

        return m_Invasibility * modifier;
    }
};

// vim:ft=enforce
