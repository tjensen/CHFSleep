modded class IngameHudVisibility
{
    private IngameHud m_CHF_Hud;

    override void SetContextFlag(EHudContextFlags flag, bool state)
    {
        super.SetContextFlag(flag, state);

        // Inefficient, but good enough, for now.
        if (m_CHF_Hud)
        {
            m_CHF_Hud.CHF_UpdateTiredness();
        }
    }

    void CHF_SetHud(IngameHud hud)
    {
        m_CHF_Hud = hud;
    }
};

// vim:ft=enforce
