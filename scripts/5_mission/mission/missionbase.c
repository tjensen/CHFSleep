modded class MissionBase
{
    void MissionBase()
    {
        if (!GetGame().IsDedicatedServer()) // Register server->client RPCs
        {
            GetRPCManager().AddRPC("ZS_RPC", "RPC_SendSleepDataToClient", this, SingeplayerExecutionType.Client);
        }
        else // Register client->server RPCs
        {
            GetRPCManager().AddRPC("ZS_RPC", "RPC_SendReceivedSleepDataToServer", this, SingeplayerExecutionType.Server);
            GetRPCManager().AddRPC("ZS_RPC", "RPC_SendReloadConfigRequestToServer", this, SingeplayerExecutionType.Server);
        }
    }

    // This is used by the server to send important server-side config data to the client
    void RPC_SendSleepDataToClient(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type == CallType.Client && !GetGame().IsDedicatedServer())
        {
            Param8< bool, bool, bool, bool, int, float, float, bool > data;
            if (!ctx.Read(data))
            {
                Print("[CHFSleep] Error sync'ing server-side data to client in RPC_SendSleepDataToClient");
                return;
            }

            PlayerBase player;
            PlayerBase.CastTo(player, GetGame().GetPlayer());
            if (player)
            {
                // Bools
                player.m_OnlyShowSleepOnInventory = data.param1;
                player.m_HideHudWhileSleeping = data.param2;
                player.m_AllowInventoryWhileSleep = data.param3;
                player.m_OnlyBlurScreen = data.param4;
                player.m_AttenuateSound = data.param8;

                // Ints
                player.m_OnlyShowSleepAbovePercent = data.param5;

                // Floats
                player.m_TirednessHudX = data.param6;
                player.m_TirednessHudY = data.param7;
                player.m_ReceivedSleepConfig = true;

                // Tell server we've confirmed that we've received the config data
                GetRPCManager().SendRPC("ZS_RPC", "RPC_SendReceivedSleepDataToServer", new Param1< PlayerBase >(player), true, NULL);
            }
        }
    }

    // This is used by the client to request the server to reload the json config file
    void RPC_SendReloadConfigRequestToServer(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type == CallType.Server && GetGame().IsDedicatedServer())
        {
            Param1 <PlayerBase> dataPlayer;
            if (!ctx.Read(dataPlayer))
            {
                Print("[CHFSleep] Error sync'ing client-side data to server in RPC_SendReloadConfigRequestToServer");
                return;
            }

            if (GetZenSleepConfig().AdminSteam64ID != dataPlayer.param1.GetIdentity().GetPlainId())
            {
                return;
            }

            dataPlayer.param1.ZS_SendMessage("Reloading ZenSleep config...");
            GetZenSleepConfig().Load();

            // Send new config update to all players on the server after a brief pause to ensure the new config has successfully loaded
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.UpdateAllPlayersSleepConfig, 1000, false);
        }
    }

    // Updates all players to let them know that the server's sleep config settings have changed
    void UpdateAllPlayersSleepConfig()
    {
        array<Man> all_players = new array<Man>;
        GetGame().GetPlayers(all_players);
        for (int i = 0; i < all_players.Count(); i++)
        {
            PlayerBase player;
            Class.CastTo(player, all_players.Get(i));
            if (player)
            {
                player.SyncServerConfig();
                player.SendSleepDataToClient();
            }
        }
    }
};

// vim:ft=enforce
