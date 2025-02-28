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
            player.CHFSleep_SendMessage("Giving tiredness penalty: " + penalty);
        }

        player.InsertAgent(CHFSleep_Agents.TIREDNESS, penalty);
    }
};

// vim:ft=enforce
