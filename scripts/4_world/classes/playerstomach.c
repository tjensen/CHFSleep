/* Copyright (c) 2022-2025 The Crimson Zamboni
 *
 * This Software is licensed for non-commercial use only, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 */

modded class PlayerStomach
{
    const int CHF_MARKER = 1128809984;

    float m_CHF_SubstanceQuantity = 0;
    float m_CHF_SubstanceStrength = 0;

    override void ClearContents()
    {
        super.ClearContents();

        m_CHF_SubstanceQuantity = 0;
        m_CHF_SubstanceStrength = 0;
    }

    override void ProcessNutrients(float delta_time)
    {
        super.ProcessNutrients(delta_time);

        float digestion_points_per_item = DIGESTION_POINTS * delta_time;

        float digestibility = 2;  // see: cfgLiquidDefinitions -> Water, Vodka, Beer, etc.

        if (m_CHF_SubstanceQuantity > 0)
        {
            float digestedSubstance = Math.Min(
                digestion_points_per_item * digestibility, m_CHF_SubstanceQuantity);
            m_CHF_SubstanceQuantity -= digestedSubstance;

            float delta = digestedSubstance * -m_CHF_SubstanceStrength;
            m_Player.InsertAgent(CHFSleep_Agents.TIREDNESS, delta);

            if (delta > 0)
            {
                m_Player.GetStatHeatBuffer().Add(delta);
            }
        }
    }

    override void PrintUpdate()
    {
        super.PrintUpdate();

        PrintFormat("Substance: %1 (%2)", m_CHF_SubstanceQuantity, m_CHF_SubstanceStrength);
        Print("================================");
    }

    override void OnStoreSave(ParamsWriteContext ctx)
    {
        super.OnStoreSave(ctx);

        ctx.Write(CHF_MARKER);
        ctx.Write(m_CHF_SubstanceQuantity);
        ctx.Write(m_CHF_SubstanceStrength);
    }

    override bool OnStoreLoad(ParamsReadContext ctx, int version)
    {
        super.OnStoreLoad(ctx, version);

        int marker;
        if (!ctx.Read(marker))
        {
            return false;
        }

        if (!ctx.Read(m_CHF_SubstanceQuantity))
        {
            return false;
        }

        if (!ctx.Read(m_CHF_SubstanceStrength))
        {
            return false;
        }

        if (marker != CHF_MARKER)
        {
            m_CHF_SubstanceQuantity = 0;
            m_CHF_SubstanceStrength = 0;
        }

        return true;
    }

    void CHF_AddSubstance(float amount, float strength)
    {
        m_CHF_SubstanceStrength = Math.Lerp(
            m_CHF_SubstanceStrength, strength, amount / (m_CHF_SubstanceQuantity + amount));
        m_CHF_SubstanceQuantity += amount;
    }
};

// vim:ft=enforce
