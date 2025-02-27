modded class AntiChemInjector
{
    override void OnApply(PlayerBase player)
    {
        super.OnApply(player);

        int penaltyPct = GetCHFSleepConfig().GetEnergyDrink("AntiChemInjector").EnergyGained;
        if (penaltyPct == 0)
        {
            return;
        }

        float penalty = (float)player.MAX_TIREDNESS * ((float)penaltyPct / 100.0);

        if (GetCHFSleepConfig().DebugOn)
        {
            player.ZS_SendMessage("Giving tiredness penalty: " + penalty);
        }

        player.InsertAgent(ZenSleep_Agents.TIREDNESS, penalty);
    }
};

// vim:ft=enforce
