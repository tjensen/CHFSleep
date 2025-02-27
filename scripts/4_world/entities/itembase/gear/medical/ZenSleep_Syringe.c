class ZenSleep_Syringe : Inventory_Base
{
    override void SetActions()
    {
        super.SetActions();
        AddAction(ActionInjectTarget);
        AddAction(ActionInjectSelf);
    }

    override void OnApply(PlayerBase player)
    {
        int penaltyPct = GetCHFSleepConfig().GetEnergyDrink("ZenSleep_Syringe").EnergyGained;
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
            player.ZS_SendMessage("Giving tiredness penalty: " + penalty);
        }

        player.InsertAgent(ZenSleep_Agents.TIREDNESS, penalty);

        // Drop used syringe
        ItemBase junk = ItemBase.Cast(GetGame().CreateObjectEx(GetCHFSleepConfig().UsedSleepSyringeType, player.GetPosition(), ECE_PLACE_ON_SURFACE));
        if (junk)
        {
            junk.SetHealth("", "Health", 1);
            junk.SetQuantity(0, false, false); // false, false overrides the game deleting edibles with <= 0 quantity.
        }
    }
};

class ZenSleep_Empty_Syringe : Inventory_Base {};

// vim:ft=enforce
