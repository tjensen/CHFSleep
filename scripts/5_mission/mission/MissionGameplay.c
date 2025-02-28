modded class MissionGameplay
{
    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);

        // Get player
        autoptr PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        // Get input controller
        autoptr Input chfInput = Input.Cast(GetGame().GetInput());

        if (!player || !chfInput)
            return;

        // If a menu is open stop here
        if (GetGame().GetUIManager().GetMenu() != null || GetGame().GetUIManager().IsCursorVisible())
        {
            return;
        }

        if (chfInput.LocalPress("UACHFSleep_RefreshConfig")) // Sends request to server to reload json config if player is admin
        {
            player.RequestServerConfigReload();
        } else
        if (chfInput.LocalPress("UACHFSleep_SleepKey")) // Triggers the lie-down emote if the player can lie down ingame
        {
            bool canSleep = player.GetEmoteManager().CanPlayEmote(EmoteConstants.ID_EMOTE_LYINGDOWN);

            if (canSleep)
            {
                if (player.GetEmoteManager())
                {
                    player.GetEmoteManager().CreateEmoteCBFromMenu(EmoteConstants.ID_EMOTE_LYINGDOWN);
                }
            }
        }
    }
};

// vim:ft=enforce
