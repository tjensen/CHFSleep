modded class Morphine
{
    override void OnApply(PlayerBase player)
    {
        super.OnApply(player);

        int penaltyPct = GetCHFSleepConfig().GetEnergyDrink("Morphine").EnergyGained;
        if (penaltyPct == 0)
        {
            return;
        }

        float penalty = (float)player.MAX_TIREDNESS * ((float)penaltyPct / 100.0);

        // If the penalty is supposed to be negative we need to flip it to positive as we're ADDING tiredness
        if (penaltyPct < 0)
        {
            penalty = Math.AbsFloat(penalty);
        }

        if (GetCHFSleepConfig().DebugOn)
        {
            player.CHFSleep_SendMessage("Giving tiredness penalty: " + penalty);
        }

        player.InsertAgent(CHFSleep_Agents.TIREDNESS, penalty);
    }
};

// vim:ft=enforce
