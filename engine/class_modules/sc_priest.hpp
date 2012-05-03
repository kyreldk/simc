// ==========================================================================
// Dedmonwakeen's Raid DPS/TPS Simulator.
// Send questions to natehieter@gmail.com
// ==========================================================================

#include "simulationcraft.hpp"

#ifndef SC_PRIEST_HPP
#define SC_PRIEST_HPP

#if SC_PRIEST == 1

namespace remove_dots_event {
struct remove_dots_event_t;
}

struct priest_t;

struct priest_targetdata_t : public targetdata_t
{
  dot_t*  dots_devouring_plague;
  dot_t*  dots_shadow_word_pain;
  dot_t*  dots_vampiric_touch;
  dot_t*  dots_holy_fire;
  dot_t*  dots_renew;

  buff_t* buffs_power_word_shield;
  buff_t* buffs_divine_aegis;
  buff_t* buffs_spirit_shell;

  buff_t* debuffs_mind_spike;

  remove_dots_event::remove_dots_event_t* remove_dots_event;

  priest_targetdata_t( priest_t* p, player_t* target );
};

struct priest_pet_t;
struct priest_guardian_pet_t;

struct priest_t : public player_t
{
  // Buffs

  struct buffs_t
  {
    // Talents
    buff_t* twist_of_fate;

    // Discipline
    buff_t* holy_evangelism;
    buff_t* dark_archangel;
    buff_t* holy_archangel;
    buff_t* inner_fire;
    buff_t* inner_focus;
    buff_t* inner_will;

    // Holy
    buff_t* chakra_pre;
    buff_t* chakra_chastise;
    buff_t* chakra_sanctuary;
    buff_t* chakra_serenity;
    buff_t* serenity;

    // Shadow
    buff_t* shadow_word_death_reset_cooldown;
    buff_t* mind_surge;
    buff_t* glyph_mind_spike;
    buff_t* shadowform;
    buff_t* vampiric_embrace;
    buff_t* shadow_of_death;
    buff_t* surge_of_darkness;
  } buffs;

  // Talents
  struct talents_t
  {
    const spell_data_t* void_tendrils;
    const spell_data_t* psyfiend;
    const spell_data_t* dominate_mind;
    const spell_data_t* body_and_soul;
    const spell_data_t* angelic_feather;
    const spell_data_t* phantasm;
    const spell_data_t* from_darkness_comes_light;
    const spell_data_t* mindbender;
    const spell_data_t* archangel;
    const spell_data_t* desperate_prayer;
    const spell_data_t* void_shift;
    const spell_data_t* angelic_bulwark;
    const spell_data_t* twist_of_fate;
    const spell_data_t* power_infusion;
    const spell_data_t* divine_insight;
    const spell_data_t* cascade;
    const spell_data_t* divine_star;
    const spell_data_t* halo;
  } talents;

  // Specialization Spells
  struct specs_t
  {
    // General

    // Discipline
    const spell_data_t* meditation_disc;
    const spell_data_t* divine_aegis;
    const spell_data_t* grace;
    const spell_data_t* evangelism;
    const spell_data_t* train_of_thought;
    const spell_data_t* divine_fury;

    // Holy
    const spell_data_t* meditation_holy;
    const spell_data_t* revelations;
    const spell_data_t* chakra_chastise;
    const spell_data_t* chakra_sanctuary;
    const spell_data_t* chakra_serenity;

    // Shadow
    const spell_data_t* devouring_plague;
    const spell_data_t* mind_surge;
    const spell_data_t* spiritual_precision;
    const spell_data_t* shadowform;
    const spell_data_t* shadowy_apparitions;
    const spell_data_t* shadowfiend_cooldown_reduction;
  } spec;

  // Mastery Spells
  struct mastery_spells_t
  {
    const spell_data_t* shield_discipline;
    const spell_data_t* echo_of_light;
    const spell_data_t* shadowy_recall;
  } mastery_spells;

  // Cooldowns
  struct cooldowns_t
  {
    cooldown_t* mind_blast;
    cooldown_t* shadowfiend;
    cooldown_t* mindbender;
    cooldown_t* chakra;
    cooldown_t* inner_focus;
    cooldown_t* penance;
  } cooldowns;

  // Gains
  struct gains_t
  {
    gain_t* dispersion;
    gain_t* shadowfiend;
    gain_t* mindbender;
    gain_t* archangel;
    gain_t* hymn_of_hope;
    gain_t* shadow_orb_mb;
    gain_t* devouring_plague_health;
    gain_t* vampiric_touch_mana;
    gain_t* vampiric_touch_mastery_mana;
  } gains;

  // Benefits
  struct benefits_t
  {
    std::array<benefit_t*, 4> mind_spike;
    benefits_t() { range::fill( mind_spike, 0 ); }
  } benefits;

  // Procs
  struct procs_t
  {
    proc_t* mastery_extra_tick;
    proc_t* shadowy_apparition;
    proc_t* mind_surge;
    proc_t* from_darkness_comes_light;
    proc_t* shadowfiend_cooldown_reduction;
  } procs;

  // Special

  struct spells_t
  {
    std::queue<spell_t*> apparitions_free;
    std::list<spell_t*>  apparitions_active;
    heal_t* echo_of_light;
    bool echo_of_light_merged;
    spells_t() : echo_of_light(), echo_of_light_merged() {}
  } spells;


  // Random Number Generators
  struct rngs_t
  {
    rng_t* mastery_extra_tick;
    rng_t* shadowy_apparitions;
  } rngs;

  // Pets
  struct pets_t
  {
    pet_t* shadowfiend;
    pet_t* mindbender;
    pet_t* lightwell;
  } pets;

  // Options
  int initial_shadow_orbs;
  std::string atonement_target_str;
  std::vector<player_t *> party_list;

  // Glyphs
  struct glyphs_t
  {
    const spell_data_t* circle_of_healing;
    const spell_data_t* dispersion;
    const spell_data_t* holy_nova;
    const spell_data_t* inner_fire;
    const spell_data_t* lightwell;
    const spell_data_t* penance;
    const spell_data_t* power_word_shield;
    const spell_data_t* prayer_of_mending;
    const spell_data_t* renew;
    const spell_data_t* smite;

    // Mop
    const spell_data_t* atonement;
    const spell_data_t* holy_fire;
    const spell_data_t* mind_spike;
    const spell_data_t* strength_of_soul;
    const spell_data_t* inner_sanctum;

    const spell_data_t* mind_flay;
    const spell_data_t* mind_blast;
    const spell_data_t* vampiric_touch;
    const spell_data_t* vampiric_embrace;
    const spell_data_t* fortitude;
  } glyphs;

  // Constants
  struct constants_t
  {
    double meditation_value;
  } constants;

  priest_t( sim_t* sim, const std::string& name, race_type_e r = RACE_NIGHT_ELF );

  // Character Definition
  virtual priest_targetdata_t* new_targetdata( player_t* target )
  { return new priest_targetdata_t( this, target ); }
  virtual void      init_base();
  virtual void      init_gains();
  virtual void      init_benefits();
  virtual void      init_rng();
  virtual void      init_spells();
  virtual void      init_buffs();
  virtual void      init_values();
  virtual void      init_actions();
  virtual void      init_procs();
  virtual void      init_scaling();
  virtual void      reset();
  virtual void      init_party();
  virtual void      create_options();
  virtual bool      create_profile( std::string& profile_str, save_type_e=SAVE_ALL, bool save_html=false ) const;
  virtual action_t* create_action( const std::string& name, const std::string& options );
  virtual pet_t*    create_pet( const std::string& name, const std::string& type = std::string() );
  virtual void      create_pets();
  virtual void      copy_from( player_t* source );
  virtual int       decode_set( const item_t& ) const;
  virtual resource_type_e primary_resource() const { return RESOURCE_MANA; }
  virtual role_type_e primary_role() const;
  virtual void      combat_begin();
  virtual double    composite_armor() const;
  virtual double    composite_spell_power( school_type_e school ) const;
  virtual double    composite_spell_hit() const;
  virtual double    composite_player_multiplier( school_type_e school, const action_t* a = NULL ) const;
  virtual double    composite_movement_speed() const;

  virtual double    matching_gear_multiplier( attribute_type_e attr ) const;

  virtual double    target_mitigation( double amount, school_type_e school, dmg_type_e, result_type_e, action_t* a=0 );

  virtual double    shadowy_recall_chance() const;

  void fixup_atonement_stats( const std::string& trigger_spell_name, const std::string& atonement_spell_name );
  virtual void pre_analyze_hook();
};

// ==========================================================================
// Priest Pet
// ==========================================================================

namespace priest_pet_stats{
struct _weapon_list_t;
}
struct priest_pet_t : public pet_t
{
  double ap_per_owner_sp;
  int stats_avaiable;
  int stats2_avaiable;
  pet_type_e _pet_type;
  double direct_power_mod;

  double get_attribute_base( int level, int stat_type_e, pet_type_e pet_type );
private:
  const priest_pet_stats::_weapon_list_t* get_weapon( pet_type_e pet_type );
public:
  double get_weapon_min( int level, pet_type_e pet_type );
  double get_weapon_max( int level, pet_type_e pet_type );
  double get_weapon_direct_power_mod( int level, pet_type_e pet_type );
  timespan_t get_weapon_swing_time( int level, pet_type_e pet_type );
  priest_pet_t( sim_t* sim, priest_t* owner, const std::string& pet_name, pet_type_e pt, bool guardian = false );
  virtual bool ooc_buffs() { return true; }
  virtual void init_base();
  virtual void schedule_ready( timespan_t delta_time=timespan_t::zero(),
                               bool   waiting=false );
  virtual double composite_spell_haste() const;
  virtual double composite_attack_haste() const;
  virtual double composite_spell_power( school_type_e school ) const;
  virtual double composite_attack_power() const;
  virtual double composite_attack_crit( const weapon_t* ) const;
  virtual double composite_spell_crit() const;
  virtual double composite_player_multiplier( school_type_e school, const action_t* a ) const;
  virtual double composite_attack_expertise( const weapon_t* ) const { return owner -> composite_spell_hit() + owner -> composite_attack_expertise() - ( owner -> buffs.heroic_presence -> up() ? 0.01 : 0.0 ); }
  virtual double composite_attack_hit() const { return owner -> composite_spell_hit(); }
  virtual resource_type_e primary_resource() const { return RESOURCE_ENERGY; }
  priest_t* o() const
  { return debug_cast<priest_t*>( owner ); }
};

// ==========================================================================
// Priest Guardian Pet
// ==========================================================================

struct priest_guardian_pet_t : public priest_pet_t
{
  priest_guardian_pet_t( sim_t* sim, priest_t* owner, const std::string& pet_name, pet_type_e pt );
  virtual void summon( timespan_t duration=timespan_t::zero() );
};

// ==========================================================================
// Base Pet for Shadowfiend and Mindbender
// ==========================================================================

struct base_fiend_pet_t : public priest_guardian_pet_t
{
  struct buffs_t
  {
    buff_t* shadowcrawl;
  } buffs;
  struct gains_t
  {
    gain_t* fiend;
  } gains;
  const spell_data_t* shadowcrawl;
  const spell_data_t* mana_leech;
  action_t* shadowcrawl_action;

  base_fiend_pet_t( sim_t* sim, priest_t* owner, pet_type_e pt, const std::string& name = "basefiend" );
  virtual void init_base();
  virtual action_t* create_action( const std::string& name,
                                   const std::string& options_str );
  virtual void init_spells();
  virtual void init_buffs();
  virtual void init_gains();
  virtual void init_resources( bool force );
  virtual void summon( timespan_t duration );
};

// ==========================================================================
// Pet Shadowfiend
// ==========================================================================

struct shadowfiend_pet_t : public base_fiend_pet_t
{
  shadowfiend_pet_t( sim_t* sim, priest_t* owner, const std::string& name = "shadowfiend" );
  virtual void init_spells();
};

// ==========================================================================
// Pet Mindbender
// ==========================================================================

struct mindbender_pet_t : public base_fiend_pet_t
{
  mindbender_pet_t( sim_t* sim, priest_t* owner, const std::string& name = "mindbender" );
  virtual void init_spells();
};

#endif

#endif
