modded class IngameHud
{
    // Tiredness HUD
    ProgressBarWidget m_Tiredness = NULL;
    Widget m_TirednessIconPanel = NULL;
    Widget m_TirednessBarPanel = NULL;
    Widget m_SleepModLayout = NULL;
    Widget m_SleepModHudPanel = NULL;
    float m_SleepHudX = 0.855; // Tiredness HUD location on the GUI - can be overridden by server config
    float m_SleepHudY = 0.02; // Tiredness HUD location on the GUI - can be overridden by server config
    bool m_ShowGameHUD = true;

    // Initialize the relevant widgets for this mod
    override void Init(Widget hud_panel_widget)
    {
        super.Init(hud_panel_widget);

        // Tiredness HUD
        Class.CastTo(m_SleepModLayout, GetGame().GetWorkspace().CreateWidgets("chfsleep/data/layout/ZenSleepLayout.layout"));
        ProgressBarWidget.CastTo(m_Tiredness, m_SleepModLayout.FindAnyWidget("SleepBar"));
        m_TirednessIconPanel = m_SleepModLayout.FindAnyWidget("SleepIconPanel");
        m_TirednessBarPanel = m_SleepModLayout.FindAnyWidget("SleepBarPanel");
        m_SleepModHudPanel = m_SleepModLayout.FindAnyWidget("HudPanel_Tiredness");

        if (!m_Tiredness || !m_TirednessIconPanel || !m_TirednessBarPanel || !m_SleepModHudPanel)
        {
            Print("[ZenSleepHUD] Failed to load UI layout!");
            return;
        }

        m_SleepModHudPanel.SetPos(m_SleepHudX, m_SleepHudY);
        m_SleepModHudPanel.Show(false);

        m_HudVisibility.CHF_SetHud(this);
    }

    // Sets the tiredness of our meter
    override void SetTiredness(int value, int range)
    {
        if (!m_Tiredness)
        {
            return;
        }

        m_Tiredness.SetCurrent((value / range) * 100);
        CHF_UpdateTiredness();
    }

    // Refreshes entire hud visibility - we also check our tiredness meter visibility here.
    override void RefreshHudVisibility()
    {
        super.RefreshHudVisibility();

        if (!m_Tiredness || !m_TirednessIconPanel || !m_TirednessBarPanel)
        {
            // Something has gone wrong loading UI - stop here.
            return;
        }

        CHF_UpdateTiredness();
    }

    void CHF_UpdateTiredness()
    {
        if (!m_ShowGameHUD)
        {
            m_SleepModHudPanel.Show(false);
            return;
        }

        // Check if only show while tabbed is enabled from server config and if our inventory is open
        bool overrideSleep = true;
        auto player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player || !player.IsAlive() || !player.m_ReceivedSleepConfig)
        {
            m_SleepModHudPanel.Show(false);

            return;
        }

        // Check if we need to move the position of the tiredness meter based on server config
        if (m_SleepModHudPanel)
        {
            if (m_SleepHudX != player.m_TirednessHudX || m_SleepHudY != player.m_TirednessHudY)
            {
                m_SleepModHudPanel.SetPos(player.m_TirednessHudX, player.m_TirednessHudY);
                m_SleepModHudPanel.GetPos(m_SleepHudX, m_SleepHudY);
            }
        }

        bool inInventory = GetHudVisibility().IsContextFlagActive(EHudContextFlags.INVENTORY_OPEN);

        // If only show on inventory is turned on, check if we're sleeping or have inventory open
        if (player.m_OnlyShowSleepOnInventory)
        {
            overrideSleep = player.m_IsSleeping || inInventory;
        }

        // If we have only show above certain tiredness percent turned on, check the threshold
        if (player.m_OnlyShowSleepAbovePercent != 0)
        {
            overrideSleep = player.m_IsSleeping || inInventory || player.GetTiredPercent() > (float)player.m_OnlyShowSleepAbovePercent;
        }

        // Check if this hud should be visible with the rest of the player hud
        bool shouldShow = !GetHudVisibility().IsContextFlagActive(IngameHudVisibility.HUD_HIDE_FLAGS);

        // Set sleep hud visibility
        m_SleepModHudPanel.Show(shouldShow && overrideSleep);
    }

    // Ensures that we hide the sleep HUD whenever the main HUD is hidden
    override void Show(bool show)
    {
        super.Show(show);
        m_ShowGameHUD = show;
    }
};

// vim:ft=enforce
