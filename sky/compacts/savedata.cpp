#include "sky/control.h"

Compact *SkyControl::_saveLoadCpts[833] = {
	// 0compact.asm:
		// Z_compac.inc:
		&SkyCompact::forklift_cpt,
		&SkyCompact::coordinate_test,
		&SkyCompact::text_1,
		&SkyCompact::text_2,
		&SkyCompact::text_3,
		&SkyCompact::text_4,
		&SkyCompact::text_5,
		&SkyCompact::text_6,
		&SkyCompact::text_7,
		&SkyCompact::text_8,
		&SkyCompact::text_9,
		&SkyCompact::text_10,
		&SkyCompact::text_11,
		&SkyCompact::joey,
		// SkyCompact::joey_auto uint8*
		&SkyCompact::joey_park,
		//SkyCompact::park_table uint16*
		// c68 dup 0
		&SkyCompact::foster,
		&SkyCompact::floor,
		//SkyCompact::high_floor_table uint16*
		// l_talk_s2 dup 0
		&SkyCompact::r_talk_s2,
		// talk 1 dup 0
		&SkyCompact::talk2,
		&SkyCompact::low_floor,
		&SkyCompact::stairs,
		&SkyCompact::upstairs,
		&SkyCompact::bar,
		&SkyCompact::door,
		&SkyCompact::small_door,
		&SkyCompact::right_exit0,
		&SkyCompact::outside_ledge,
		&SkyCompact::r1_door,
		&SkyCompact::s2_floor,
		&SkyCompact::lamb,
		//SkyCompact::lamb_auto uint8*
		&SkyCompact::monitor,
		//SkyCompact::monitor_auto uint8*
		&SkyCompact::anita,
		&SkyCompact::whole_screen,
		// Objects.inc:
		&SkyCompact::menu_bar,
		&SkyCompact::left_arrow,
		&SkyCompact::right_arrow,
		&SkyCompact::blank1,
		&SkyCompact::blank2,
		&SkyCompact::blank3,
		&SkyCompact::blank4,
		&SkyCompact::blank5,
		&SkyCompact::blank6,
		&SkyCompact::blank7,
		&SkyCompact::blank8,
		&SkyCompact::blank9,
		&SkyCompact::blank10,
		&SkyCompact::blank11,
		&SkyCompact::crow_bar_menu,
		&SkyCompact::sarnie_menu,
		&SkyCompact::spanner_menu,
		&SkyCompact::joeyb_menu,
		&SkyCompact::citycard_menu,
		&SkyCompact::shades_menu,
		&SkyCompact::putty_menu,
		&SkyCompact::lightbulb_menu,
		&SkyCompact::wd40_menu,
		&SkyCompact::skey_menu,
		&SkyCompact::anita_card_menu,
		&SkyCompact::anchor_menu,
		&SkyCompact::magazine_menu,
		&SkyCompact::tape_menu,
		&SkyCompact::glass_menu,
		&SkyCompact::rope_menu,
		&SkyCompact::ticket_menu,
		&SkyCompact::new_cable_menu,
		&SkyCompact::secateurs_menu,
		&SkyCompact::plaster_menu,
		&SkyCompact::brick_menu,
		&SkyCompact::tongs_menu,
		&SkyCompact::dog_food_menu,
		&SkyCompact::gallcard_menu,
		//101comp.inc:
		&SkyCompact::full_screen,
		&SkyCompact::cancel_button,
		&SkyCompact::button_7,
		&SkyCompact::button_8,
		&SkyCompact::button_9,
		&SkyCompact::button_4,
		&SkyCompact::button_5,
		&SkyCompact::button_6,
		&SkyCompact::button_1,
		&SkyCompact::button_2,
		&SkyCompact::button_3,
		&SkyCompact::button_0,
		&SkyCompact::retina_scan,
		//102comp.inc:
		&SkyCompact::restart_butt,
		&SkyCompact::restore_butt,
		&SkyCompact::exit_butt,
		//85comp.inc:
	//1compact.asm:
		//0compact.inc:
		//c74 dup 0
		&SkyCompact::mini_so,
		//SkyCompact::ss_auto uint8*
		//c101 dup 0
		&SkyCompact::full_so,
		//SkyCompact::full_ss_auto uint8*
		&SkyCompact::load_point,
		&SkyCompact::fire_notice,
		//1compact.inc
		&SkyCompact::fire_notice2,
		&SkyCompact::ss_sign,
		&SkyCompact::lfan1,
		&SkyCompact::lfan2,
		&SkyCompact::smoke1,
		&SkyCompact::smoke2,
		&SkyCompact::fire1,
		&SkyCompact::fire2,
		&SkyCompact::car_up,
		&SkyCompact::car_down,
		//2compact.inc
		&SkyCompact::top_lift,
		&SkyCompact::top_lift_2,
		&SkyCompact::top_barrel,
		&SkyCompact::light_one,
		&SkyCompact::panel,
		&SkyCompact::alarm_flash,
		&SkyCompact::robot_shell,
		&SkyCompact::dead_loader,
		// exit_table dup 0
		// left_table2 dup 0
		&SkyCompact::junk1,
		&SkyCompact::junk2,
		// c4121 dup 0
		&SkyCompact::loader,
		//SkyCompact::loader_auto uint8*
		//3compact.inc:
		&SkyCompact::steve_watch,
		&SkyCompact::low_barrel,
		&SkyCompact::convey,
		&SkyCompact::joey_fly,
		&SkyCompact::furnace,
		&SkyCompact::lights1,
		&SkyCompact::eye_ball,
		&SkyCompact::furnace_door,
		&SkyCompact::slot,
		// sh dup 0
		&SkyCompact::shades,
		//SkyCompact::shade_auto uint8*
		&SkyCompact::eye_bolt,
		&SkyCompact::smoulder,
		&SkyCompact::low_lift,
		&SkyCompact::low_lift_2,
		&SkyCompact::low_lift_3,
		//4compact.inc:
		&SkyCompact::sc4_floor,
		&SkyCompact::sc4_left_exit,
		// l_talk_s4 dup 0
		&SkyCompact::r_talk_s4,
		&SkyCompact::tv_screens_s4,
		&SkyCompact::knob_s4,
		&SkyCompact::chuck_s4,
		&SkyCompact::lazer_s4,
		&SkyCompact::cupboard_s4,
		&SkyCompact::sarnie_s4,
		&SkyCompact::spanner_s4,
		&SkyCompact::monitors_s4,
		&SkyCompact::buttons_s4,
		&SkyCompact::postcard,
		&SkyCompact::notice4,
		// c43 dup 0
		&SkyCompact::jobsworth,
		//&SkyCompact::jobs_script // ------
		//SkyCompact::jobs_auto uint8*
	// 2compact.asm
		//5compact.inc:
		&SkyCompact::s6_floor,
		&SkyCompact::stairs6,
		&SkyCompact::joey_fly_6,
		&SkyCompact::left_exit_s6,
		&SkyCompact::s5_floor,
		&SkyCompact::right_exit_s5,
		&SkyCompact::right_exit_s6,
		&SkyCompact::security_exit_s6,
		&SkyCompact::s7_floor,
		&SkyCompact::left_exit_s7,
		&SkyCompact::left_exit_s5,
		&SkyCompact::skorl_guard,
		&SkyCompact::security_exit,
		&SkyCompact::s8_floor,
		&SkyCompact::right_exit_s7,
		&SkyCompact::down_exit_s8,
		&SkyCompact::wreck_guard,
		// grid 5 + 6 + 7 + 8 +	9 + 18 => dup 0
		&SkyCompact::factory_entry,
		&SkyCompact::s7_card_slot,
		&SkyCompact::lift_notice,
		&SkyCompact::lift_s7,
		&SkyCompact::linc_s7,
		&SkyCompact::lift7_light,
		&SkyCompact::cable_7,
		&SkyCompact::copter,
		// 9compact.inc:
		&SkyCompact::s9_floor,
		&SkyCompact::left_exit_s9,
		&SkyCompact::fans,
		&SkyCompact::lobby_door,
		&SkyCompact::scanner,
		&SkyCompact::lobby_slot,
		&SkyCompact::dad,
		&SkyCompact::son,
		&SkyCompact::fake_floor_9,
		&SkyCompact::linc_s9,
		// 12comp.inc:
		&SkyCompact::s12_floor,
		&SkyCompact::factory_exit,
		&SkyCompact::fact1_right_exit,
		&SkyCompact::topbelt,
		&SkyCompact::botbelt,
		&SkyCompact::pipes,
		&SkyCompact::anita_spy,
		&SkyCompact::welder,
		&SkyCompact::stump,
		&SkyCompact::console_12,
		// 13comp.inc:
		&SkyCompact::s13_floor,
		&SkyCompact::fact2_exit_left,
		&SkyCompact::fact2_exit_right,
		&SkyCompact::fact2_store_exit,
		&SkyCompact::cogs,
		&SkyCompact::gears,
		&SkyCompact::belts1,
		&SkyCompact::belts2,
		&SkyCompact::pipe1,
		&SkyCompact::pipe2,
		&SkyCompact::pipe3,
		&SkyCompact::pipe4,
		&SkyCompact::sensor,
		&SkyCompact::lite1,
		&SkyCompact::lite2,
		&SkyCompact::fact2_spy_and_window,
		&SkyCompact::fact_console,
		&SkyCompact::sensors,
		&SkyCompact::foreman,
		//SkyCompact::foreman_auto uint8*
		// 14comp.inc:
		&SkyCompact::s14_floor,
		&SkyCompact::fact3_exit_left,
		&SkyCompact::fact3_exit_right,
		&SkyCompact::locker3,
		&SkyCompact::locker2,
		&SkyCompact::locker1,
		&SkyCompact::machine,
		&SkyCompact::rad_screen,
		&SkyCompact::console_14,
		&SkyCompact::coat,
		&SkyCompact::radman,
		//SkyCompact::radman_auto uint8*
		// 15comp.inc:
		&SkyCompact::nu_floor,
		&SkyCompact::s15_flooor,
		&SkyCompact::store_exit,
		&SkyCompact::junction_box,
		&SkyCompact::whole_floor,
		&SkyCompact::flap,
		&SkyCompact::skey,
		&SkyCompact::wd40,
		&SkyCompact::floor_putty,
		// 16comp.inc:
		&SkyCompact::s16_floor,
		&SkyCompact::entrance_exit,
		&SkyCompact::reactor_console,
		&SkyCompact::reactor_door,
		&SkyCompact::reactor_lower,
		// 17comp.inc:
		&SkyCompact::s17_floor,
		&SkyCompact::core_exit,
		&SkyCompact::pulse,
		&SkyCompact::pulseb,
		&SkyCompact::anita_card,
		&SkyCompact::s18_floor,
		&SkyCompact::steam,
		&SkyCompact::power_door,
		&SkyCompact::power_motor,
		&SkyCompact::socket,
		&SkyCompact::power_switch,
		&SkyCompact::power_chair,
		&SkyCompact::left_skull,
		&SkyCompact::right_skull,
		&SkyCompact::power_bang,
		&SkyCompact::left_lever,
		&SkyCompact::right_lever,
	//3compact.asm
		// 10comp.inc:		
		&SkyCompact::s10_floor,
		&SkyCompact::left_exit_10,
		&SkyCompact::lift_10,
		&SkyCompact::lift_slot_10,
		&SkyCompact::scanner_10,
		&SkyCompact::pod,
		&SkyCompact::linc_10,
		&SkyCompact::pod_light,
		&SkyCompact::monitor_10,
		&SkyCompact::liyt_1,
		&SkyCompact::liyt_2,
		&SkyCompact::liyt_3,
		&SkyCompact::liyt_4,
		&SkyCompact::litebank,
		&SkyCompact::terminal_10,
		&SkyCompact::fake_floor_10,
		// 11comp.inc
		&SkyCompact::s11_floor,
		&SkyCompact::cable_fall,
		&SkyCompact::cable_fall2,
		&SkyCompact::smashed_window,
		&SkyCompact::bits,
		&SkyCompact::bits2,
		&SkyCompact::spy_11,
		&SkyCompact::locker_11,
		&SkyCompact::slot_11,
		&SkyCompact::soccer_1,
		&SkyCompact::soccer_2,
		&SkyCompact::soccer_3,
		&SkyCompact::soccer_4,
		&SkyCompact::soccer_5,
		&SkyCompact::slat_1,
		&SkyCompact::slat_2,
		&SkyCompact::slat_3,
		&SkyCompact::slat_4,
		&SkyCompact::slat_5,
		&SkyCompact::right_exit_11,
		// 19comp.inc:
		&SkyCompact::s19_floor,
		&SkyCompact::right_exit_19,
		&SkyCompact::left_exit_19,
		&SkyCompact::top_right_19,
		&SkyCompact::useless_char,
		// 20comp.inc:
		&SkyCompact::s20_floor,
		&SkyCompact::down_exit_20,
		&SkyCompact::reich_door_20,
		&SkyCompact::reich_slot,
		&SkyCompact::lamb_door_20,
		&SkyCompact::lamb_slot,
		&SkyCompact::shrub_1,
		&SkyCompact::shrub_2,
		&SkyCompact::shrub_3,
		&SkyCompact::gallager_bel,
		&SkyCompact::reich_window,
		&SkyCompact::lamb_window,
		// 21comp.inc:
		&SkyCompact::s21_floor,
		&SkyCompact::left_exit_21,
		&SkyCompact::lambs_books,
		&SkyCompact::lambs_chair,
		&SkyCompact::dispensor,
		&SkyCompact::cat_food,
		&SkyCompact::video,
		&SkyCompact::cassette,
		&SkyCompact::big_pict1,
		&SkyCompact::video_screen,
		&SkyCompact::big_pict2,
		&SkyCompact::big_pict3,
		&SkyCompact::cat,
		&SkyCompact::fake_floor_21,
		&SkyCompact::inner_lamb_door,
		// 22comp.inc:
		&SkyCompact::s22_floor,
		&SkyCompact::right_exit_22,
		&SkyCompact::lamb_bed,
		&SkyCompact::lamb_tv,
		&SkyCompact::fish_tank,
		&SkyCompact::fish_poster,
		&SkyCompact::pillow,
		&SkyCompact::magazine,
		&SkyCompact::reich_chair,
		&SkyCompact::cabinet,
		&SkyCompact::cert,
		&SkyCompact::reich_picture,
		&SkyCompact::fish_food,
		&SkyCompact::fake_floor_22,
		&SkyCompact::inner_reich_door,
		// 23comp.inc:
		&SkyCompact::s23_floor,
		&SkyCompact::left_exit_23,
		&SkyCompact::anchor_exit_23,
		&SkyCompact::travel_exit_23,
		&SkyCompact::bin_23,
		&SkyCompact::sculpture,
		&SkyCompact::link_23,
		&SkyCompact::wreck_23,
		&SkyCompact::small_exit_23,
		// 24comp.inc:
		&SkyCompact::s24_floor,
		&SkyCompact::left_exit_24,
		&SkyCompact::london_poster,
		&SkyCompact::new_york_poster,
		&SkyCompact::mural,
		&SkyCompact::pidgeons,
		&SkyCompact::trevor,
		&SkyCompact::ticket,
		&SkyCompact::globe,
		// 25comp.inc:
		&SkyCompact::s25_floor,
		&SkyCompact::anchor_exit_25,
		&SkyCompact::anchor,
		&SkyCompact::statue_25,
		&SkyCompact::hook,
		&SkyCompact::lazer_25,
		&SkyCompact::spark_25,
		&SkyCompact::sales_chart,
		// 26comp.inc:
		&SkyCompact::s26_floor,
		&SkyCompact::right_exit_26,
		&SkyCompact::poster1,
		&SkyCompact::poster2,
		&SkyCompact::poster3,
		&SkyCompact::poster4,
		&SkyCompact::plant_26,
		&SkyCompact::holo,
		&SkyCompact::left_exit_26,
		&SkyCompact::bio_door,
		&SkyCompact::leaflet,
		// 27comp.inc:
		&SkyCompact::s27_floor,
		&SkyCompact::right_exit_27,
		&SkyCompact::chart1,
		&SkyCompact::chart2,
		&SkyCompact::gas,
		&SkyCompact::medi_comp,
		&SkyCompact::scanner_27,
		&SkyCompact::chair_27,
		&SkyCompact::helmet_cole,
		&SkyCompact::body,
		&SkyCompact::glass_slot,
		&SkyCompact::burke,
		// SkyCompact::burke_auto uint8*
		// 28comp.inc:
		&SkyCompact::s28_floor,
		&SkyCompact::right_exit_28,
		&SkyCompact::left_exit_28,
		&SkyCompact::dustbin_28,
		&SkyCompact::up_exit_28,
		&SkyCompact::s28_sml_floor,
		&SkyCompact::small_r_28,
		&SkyCompact::small_l_28,
		&SkyCompact::lift_28,
		&SkyCompact::slot_28,
		// 29comp.inc
		&SkyCompact::s29_floor,
		&SkyCompact::lift_29,
		&SkyCompact::s29_card_slot,
		&SkyCompact::lift29_light,
		&SkyCompact::right_exit_29,
		&SkyCompact::left_exit_29,
		&SkyCompact::cable_29,
		&SkyCompact::s29_sml_floor,
		&SkyCompact::small_r_29,
		&SkyCompact::small_l_29,
	// 4compact.asm
		// 30comp.inc:
		&SkyCompact::sc30_floor,
		&SkyCompact::sc30_exit_31,
		&SkyCompact::sc30_exit_33,
		&SkyCompact::sc30_exit_36,
		&SkyCompact::sc30_court_door,
		&SkyCompact::sc30_notice,
		&SkyCompact::sc30_statue_1,
		&SkyCompact::sc30_statue_2,
		&SkyCompact::sc30_henri,
		// 31comp.inc:
		&SkyCompact::sc31_floor,
		&SkyCompact::sc31_exit_30,
		&SkyCompact::sc31_exit_32,
		&SkyCompact::sc31_exit_39,
		&SkyCompact::sc31_lift,
		&SkyCompact::sc31_lift_slot,
		&SkyCompact::sc31_end_of_rope,
		&SkyCompact::sc31_rope,
		&SkyCompact::sc31_bricks,
		&SkyCompact::sc31_plank,
		&SkyCompact::sc31_biscuits,
		&SkyCompact::sc31_guard,
		&SkyCompact::sc31_joey,
		&SkyCompact::sc31_at_watcher,
		// 32comp.inc:
		&SkyCompact::sc32_floor,
		&SkyCompact::sc32_exit_31,
		&SkyCompact::sc32_exit_33,
		&SkyCompact::sc32_lift,
		&SkyCompact::sc32_terminal,
		&SkyCompact::sc32_buzzer,
		&SkyCompact::sc32_plant_1,
		&SkyCompact::sc32_plant_2,
		&SkyCompact::sc32_plant_3,
		&SkyCompact::sc32_vincent,
		&SkyCompact::sc32_gardener,
		// 33comp.inc:
		&SkyCompact::sc33_floor,
		&SkyCompact::sc33_exit_30,
		&SkyCompact::sc33_exit_32,
		&SkyCompact::sc33_shed_door,
		&SkyCompact::sc33_lock,
		// 34comp.inc:
		&SkyCompact::sc34_floor,
		&SkyCompact::sc34_door,
		&SkyCompact::sc34_secateurs,
		&SkyCompact::sc34_tkt_machine,
		&SkyCompact::sc34_map,
		&SkyCompact::sc34_bricks,
		// 36comp.inc:
		&SkyCompact::sc36_floor,
		&SkyCompact::sc36_low_floor,
		&SkyCompact::sc36_exit_30,
		&SkyCompact::sc36_sensor,
		&SkyCompact::sc36_door,
		&SkyCompact::sc36_band,
		&SkyCompact::sc36_jukebox,
		&SkyCompact::sc36_juke_light,
		&SkyCompact::sc36_barman,
		&SkyCompact::sc36_colston,
		&SkyCompact::sc36_col_feet,
		&SkyCompact::sc36_gallagher,
		&SkyCompact::sc36_gal_legs,
		&SkyCompact::sc36_cards,
		&SkyCompact::sc36_glass,
		// babs dup 0
		&SkyCompact::sc36_babs,
		//SkyCompact::babs_auto uint8*
		// 37comp.inc:
		&SkyCompact::sc37_floor,
		&SkyCompact::sc37_holding_lid,
		&SkyCompact::sc37_flimsy_box,
		&SkyCompact::sc37_sensor,
		&SkyCompact::sc37_door,
		&SkyCompact::sc37_grill,
		&SkyCompact::sc37_big_box,
		&SkyCompact::sc37_lid,
		&SkyCompact::sc37_wine_rack,
		// 38comp.inc:
		&SkyCompact::sc38_floor,
		&SkyCompact::sc38_lift,
		&SkyCompact::sc38_statue,
		&SkyCompact::sc38_monitor,
		&SkyCompact::sc38_video,
		&SkyCompact::sc38_sofa,
		&SkyCompact::sc38_dog_tray,
		&SkyCompact::sc38_biscuits,
		// dna dup 0
		&SkyCompact::danielle,
		//SkyCompact::dan_auto uint8 *
		// spu dup 0
		&SkyCompact::spunky,
		//SkyCompact::spu_auto uint8 *
		&SkyCompact::sc38_hand_set,
		&SkyCompact::sc38_ringer,
		&SkyCompact::dog_bark_thing,
		// 39comp.inc:
		&SkyCompact::sc39_floor,
		&SkyCompact::sc39_exit_31,
		&SkyCompact::sc39_exit_40,
		&SkyCompact::sc39_exit_41,
		&SkyCompact::sc39_walters,
		// 40comp.inc:
		&SkyCompact::sc40_floor,
		&SkyCompact::sc40_exit_39,
		&SkyCompact::sc40_cabinet,
		&SkyCompact::sc40_trolley,
		&SkyCompact::sc40_locker_1,
		&SkyCompact::sc40_locker_2,
		&SkyCompact::sc40_locker_3,
		&SkyCompact::sc40_locker_4,
		&SkyCompact::sc40_locker_5,
		&SkyCompact::sc40_body_1,
		&SkyCompact::sc40_body_2,
		&SkyCompact::sc40_body_3,
		&SkyCompact::sc40_body_4,
		&SkyCompact::sc40_body_5,
		// 41comp.inc:
		&SkyCompact::sc41_floor,
		&SkyCompact::sc41_exit_39,
		&SkyCompact::sc41_heat_1,
		&SkyCompact::sc41_heat_2,
		&SkyCompact::sc41_heat_3,
		// 42comp.inc
		&SkyCompact::sc42_judge,
		&SkyCompact::sc42_clerk,
		&SkyCompact::sc42_prosecution,
		&SkyCompact::sc42_jobsworth,
		&SkyCompact::sc42_sign,
		// 44comp.inc
		&SkyCompact::sc44_floor,
		&SkyCompact::sc44_exit_45,
		&SkyCompact::sc44_grill,
		&SkyCompact::sc44_rubble,
		// 45comp.inc:
		&SkyCompact::sc45_floor,
		&SkyCompact::sc45_exit_44,
		&SkyCompact::sc45_exit_46,
		&SkyCompact::sc45_exit_47,
		// 46comp.inc:
		&SkyCompact::sc46_floor,
		&SkyCompact::sc46_exit_45,
		&SkyCompact::sc46_rubble,
		// 47comp.inc:
		&SkyCompact::sc47_floor,
		&SkyCompact::sc47_exit_45,
		&SkyCompact::sc47_exit_48,
		// 48comp.inc:
		&SkyCompact::sc48_floor,
		&SkyCompact::sc48_exit_47,
		&SkyCompact::sc48_exit_65,
		&SkyCompact::sc48_socket,
		&SkyCompact::sc48_hole,
		&SkyCompact::sc48_eyes,
		// 65comp.inc:
		&SkyCompact::sc65_floor,
		&SkyCompact::sc65_exit_48,
		&SkyCompact::sc65_exit_66,
		&SkyCompact::sc65_poster1,
		&SkyCompact::sc65_poster2,
		&SkyCompact::sc65_sign,

	// 5compact.asm
		//66comp.inc:
		&SkyCompact::sc66_hole,
		&SkyCompact::sc66_door,
		&SkyCompact::sc66_hi_beam,
		&SkyCompact::sc66_lo_beam,
		&SkyCompact::sc66_rock1,
		&SkyCompact::sc66_rock2,
		&SkyCompact::sc66_rock3,
		&SkyCompact::sc66_stones,
		//67comp.inc:
		&SkyCompact::sc67_floor,
		&SkyCompact::sc67_door,
		&SkyCompact::sc67_brickwork,
		&SkyCompact::sc67_plaster,
		&SkyCompact::sc67_plaster,
		&SkyCompact::sc67_brick,
		&SkyCompact::sc67_clot,
		&SkyCompact::sc67_vein,
		&SkyCompact::sc67_rock,
		&SkyCompact::sc67_pulse1,
		&SkyCompact::sc67_pulse2,
        &SkyCompact::sc67_pulse3,
		&SkyCompact::sc67_pulse4,
		&SkyCompact::sc67_crowbar,
		&SkyCompact::sc67_mend,
		//68comp.inc:
		&SkyCompact::sc68_floor,
		&SkyCompact::sc68_door,
		&SkyCompact::sc68_grill,
		&SkyCompact::sc68_sensor,
		&SkyCompact::sc68_stairs,
		&SkyCompact::sc68_exit,
		&SkyCompact::sc68_pulse1,
		&SkyCompact::sc68_pulse2,
		&SkyCompact::sc68_pulse3,
		&SkyCompact::sc68_pulse4,
		&SkyCompact::sc68_pulse5,
		&SkyCompact::sc68_pulse6,
		//69comp.inc:
		&SkyCompact::sc69_floor,
		&SkyCompact::sc69_exit,
		&SkyCompact::sc69_door,
		&SkyCompact::sc69_grill,
		&SkyCompact::sc69_pulse1,
		&SkyCompact::sc69_pulse2,
		&SkyCompact::sc69_pulse3,
		&SkyCompact::sc69_pulse4,
		&SkyCompact::sc69_pulse5,
		&SkyCompact::sc69_pulse6,
		//70comp.inc:
        &SkyCompact::sc70_floor,
		&SkyCompact::sc70_pit,
		&SkyCompact::sc70_door,
		&SkyCompact::sc70_iris,
		&SkyCompact::sc70_bar,
		&SkyCompact::sc70_grill,
		&SkyCompact::sc70_control,
		// 71comp.inc
		&SkyCompact::sc71_fake_floor,
		&SkyCompact::sc71_floor,
		&SkyCompact::sc71_door69,
		&SkyCompact::sc71_door72,
		&SkyCompact::sc71_locked_door,
		&SkyCompact::sc71_recharger,
		&SkyCompact::sc71_panel2,
		&SkyCompact::sc71_monitor,
		&SkyCompact::sc71_controls,
		&SkyCompact::sc71_light1,
		&SkyCompact::sc71_chlite,
		&SkyCompact::sc71_medi_slot,
		&SkyCompact::medi,
		//SkyCompact::medi_auto uint8*
		// 72comp.inc
		&SkyCompact::sc72_fake_floor,
		&SkyCompact::sc72_floor,
		&SkyCompact::sc72_door,
		&SkyCompact::sc72_exit,
		&SkyCompact::sc72_tank,
		&SkyCompact::sc72_tap,
		&SkyCompact::sc72_spill,
		&SkyCompact::sc72_grill,
		&SkyCompact::sc72_chamber1,
		&SkyCompact::sc72_cham1_light,
		&SkyCompact::sc72_chamber2,
		&SkyCompact::sc72_cham2_light,
		&SkyCompact::sc72_chamber3,
		&SkyCompact::sc72_computer,
		&SkyCompact::sc72_computer2,
        &SkyCompact::sc72_rot_light,
		//wit dup 0
		&SkyCompact::witness,
		//SkyCompact::wit_auto uint8*
		// 73comp.inc:
		&SkyCompact::sc73_floor,
		&SkyCompact::sc73_exit,
		&SkyCompact::sc73_chamber3,
		&SkyCompact::sc73_chamber4,
		&SkyCompact::sc73_cham4_light,
		&SkyCompact::sc73_chamber5,
		&SkyCompact::sc73_cham5_light,
		&SkyCompact::sc73_big_door,
		&SkyCompact::sc73_sensor,
		&SkyCompact::sc73_door,
		&SkyCompact::sc73_locked_door,
		&SkyCompact::sc73_bits,
		&SkyCompact::sc73_bits2,
		&SkyCompact::sc73_spray,
		// gal dup 0
		&SkyCompact::gallagher,
		//SkyCompact::gal_auto uint8*
		// 74comp.inc:
		&SkyCompact::sc74_floor,
		&SkyCompact::sc74_interface,
		&SkyCompact::sc74_int_slot,
		&SkyCompact::sc74_door,
		&SkyCompact::sc74_monitor1,
		&SkyCompact::sc74_monitor2,
		&SkyCompact::sc74_monitor3,
		&SkyCompact::sc74_monitor4,
		&SkyCompact::sc74_left_tv,
		&SkyCompact::sc74_right_tv,
		&SkyCompact::sc74_lights,
		&SkyCompact::sc74_terminal,
		&SkyCompact::sc74_pod,
		// 75comp.inc:
		&SkyCompact::sc75_floor,
		&SkyCompact::sc75_big_door,
		&SkyCompact::sc75_door,
		&SkyCompact::sc75_nitro_tank,
		&SkyCompact::sc75_live_tank,
		&SkyCompact::sc75_console,
		&SkyCompact::sc75_light1,
		&SkyCompact::sc75_light2,
		&SkyCompact::sc75_tongs,
		// 76comp.inc
		&SkyCompact::sc76_floor,
		&SkyCompact::sc76_door75,
		&SkyCompact::sc76_door77,
		&SkyCompact::sc76_android_1,
		&SkyCompact::sc76_android_2,
		&SkyCompact::sc76_android_3,
		&SkyCompact::sc76_console_1,
		&SkyCompact::sc76_console_2,
		&SkyCompact::sc76_console_3,
		&SkyCompact::sc76_cabinet_1,
		&SkyCompact::sc76_cabinet_2,
		&SkyCompact::sc76_cabinet_3,
		&SkyCompact::sc76_board_1,
		&SkyCompact::sc76_board_2,
		&SkyCompact::sc76_board_3,
		&SkyCompact::sc76_light1,
		&SkyCompact::sc76_light2,
		&SkyCompact::sc76_light3,
		&SkyCompact::sc76_light4,
		&SkyCompact::sc76_light5,
		&SkyCompact::sc76_light6,
		&SkyCompact::sc76_light7,
		&SkyCompact::sc76_light8,
		&SkyCompact::sc76_light9,
		&SkyCompact::ken,
		//SkyCompact::ken_auto uint8*
        // 77comp.inc:
		&SkyCompact::sc77_floor,
		&SkyCompact::sc77_door76,
		&SkyCompact::sc77_big_door,
		&SkyCompact::sc77_tank_1,
		&SkyCompact::sc77_tank_2,
		&SkyCompact::sc77_hand_1,
		&SkyCompact::sc77_hand_2,
		// 78comp.inc:
		&SkyCompact::sc78_ledge,
		&SkyCompact::sc78_pipe,
		&SkyCompact::sc78_big_door,
		&SkyCompact::sc78_exit,
		&SkyCompact::sc78_support,
		// 79comp.inc:
		&SkyCompact::sc79_pipe,
		&SkyCompact::sc79_exit,
		&SkyCompact::sc79_support,
		&SkyCompact::sc79_ladder,
		&SkyCompact::sc79_knot,
		&SkyCompact::sc79_rope,
		// 80comp.inc:
		&SkyCompact::sc80_spout,
		&SkyCompact::sc80_ladder,
		&SkyCompact::sc80_rope,
		&SkyCompact::sc80_orifice,
		&SkyCompact::sc80_exit,
		&SkyCompact::sc80_sample,
		&SkyCompact::sc80_goo,
		&SkyCompact::sc80_bubble1,
		&SkyCompact::sc80_bubble2,
		&SkyCompact::sc80_bubble3,
		&SkyCompact::sc80_bubble4,
		&SkyCompact::sc80_bubble5,
		&SkyCompact::sc80_bubble6,
		&SkyCompact::sc80_bubble7,
		&SkyCompact::sc80_bubble8,
		&SkyCompact::sc80_bubble9,
		&SkyCompact::sc80_bubble10,
		&SkyCompact::sc80_bubble11,
		&SkyCompact::sc80_bubble12,
		// 81comp.inc:
		&SkyCompact::sc81_father,
		&SkyCompact::sc81_father_sat,
		&SkyCompact::sc81_foster_sat,
		&SkyCompact::sc81_ken_sat,
		&SkyCompact::sc81_door,
		&SkyCompact::sc81_chair,
		&SkyCompact::sc81_helmet,
		&SkyCompact::sc81_tent1,
		&SkyCompact::sc81_tent2,
		&SkyCompact::sc81_tent3,
		&SkyCompact::sc81_tent4,
		&SkyCompact::sc81_tent5,
		&SkyCompact::sc81_tent6,
		&SkyCompact::sc81_big_tent1,
		&SkyCompact::sc81_big_tent2,
		&SkyCompact::sc81_big_tent3,
		// 82comp.inc:
		&SkyCompact::sc82_jobsworth,
	//6compact.asm
		// 90comp.inc:
		&SkyCompact::sc90_floor,
		&SkyCompact::sc90_smfloor,
		&SkyCompact::door_l90,
		&SkyCompact::door_l90f,
		&SkyCompact::door_r90,
		&SkyCompact::door_r90f,
		&SkyCompact::join_object,
		&SkyCompact::oscillator,
		&SkyCompact::eyeball_90,
		// 91comp.inc:
		&SkyCompact::sc91_floor,
		&SkyCompact::door_l91,
		&SkyCompact::door_l91f,
		&SkyCompact::door_r91,
		&SkyCompact::door_r91f,
		&SkyCompact::door_t91,
		&SkyCompact::door_t91r,
		&SkyCompact::bag_91,
		&SkyCompact::decomp_obj,
		&SkyCompact::decrypt_obj,
		&SkyCompact::report_book,
		&SkyCompact::eyeball_91,
		// 92comp.inc:
		&SkyCompact::slab1,
		&SkyCompact::slab2,
		&SkyCompact::slab3,
		&SkyCompact::slab4,
		&SkyCompact::slab5,
		&SkyCompact::slab6,
		&SkyCompact::slab7,
		&SkyCompact::slab8,
		&SkyCompact::slab9,
		&SkyCompact::bridge_a,
		&SkyCompact::bridge_b,
		&SkyCompact::bridge_c,
		&SkyCompact::bridge_d,
		&SkyCompact::bridge_e,
		&SkyCompact::bridge_f,
		&SkyCompact::bridge_g,
		&SkyCompact::bridge_h,
		&SkyCompact::door_l92,
		&SkyCompact::door_l92f,
		&SkyCompact::door_r92,
		&SkyCompact::door_r92r,
		&SkyCompact::green_circle,
		&SkyCompact::red_circle,
		// 93comp.inc:
		&SkyCompact::sc93_floor,
		&SkyCompact::door_l93,
		&SkyCompact::door_l93f,
		&SkyCompact::persona,
		&SkyCompact::adjust_book,
		// 94comp.inc:
		&SkyCompact::sc94_floor,
		&SkyCompact::door_l94,
		&SkyCompact::door_l94r,
		&SkyCompact::door_r94,
		&SkyCompact::door_r94r,
		&SkyCompact::hologram_pad,
		&SkyCompact::hologram_a,
		&SkyCompact::hologram_b,
		// 95comp.inc:
		&SkyCompact::sc95_floor,
		&SkyCompact::door_l95,
		&SkyCompact::door_l95f,
		&SkyCompact::door_r95,
		&SkyCompact::door_r95f,
		&SkyCompact::door_t95,
		&SkyCompact::door_t95r,
		&SkyCompact::guardian,
		&SkyCompact::weight,
		// 96comp.inc:
		&SkyCompact::sc96_floor,
		&SkyCompact::door_l96,
		&SkyCompact::door_l96f,
		&SkyCompact::crystal,
		&SkyCompact::virus,
		// lincmenu.inc:
		&SkyCompact::info_menu,
		&SkyCompact::read_menu,
		&SkyCompact::open_menu,
		&SkyCompact::charon_menu,
		&SkyCompact::orders_menu,
		&SkyCompact::orders2_menu,
		&SkyCompact::join_menu,
		&SkyCompact::green_menu,
		&SkyCompact::red_menu,
		&SkyCompact::report_menu,
		&SkyCompact::report2_menu,
		&SkyCompact::decomp_menu,
		&SkyCompact::decrypt_menu,
		&SkyCompact::persona_menu,
		&SkyCompact::adjust_menu,
		&SkyCompact::adjust2_menu,
		&SkyCompact::playbak_menu,
		&SkyCompact::blind_menu,
		&SkyCompact::oscill_menu,
		&SkyCompact::kill_menu,
		&SkyCompact::virus_menu,
		// linc_gen.inc:
		&SkyCompact::window_1,
		&SkyCompact::window_2,
		&SkyCompact::window_3,
		&SkyCompact::window_4,
		&SkyCompact::info_button
};

uint8 *SkyControl::_saveLoadARs[18] = {
	SkyCompact::joey_auto,
	SkyCompact::lamb_auto,
	SkyCompact::monitor_auto,
	SkyCompact::ss_auto,
	SkyCompact::full_ss_auto,
	SkyCompact::loader_auto,
	SkyCompact::shades_auto,
	SkyCompact::jobs_auto,
	SkyCompact::foreman_auto,
	SkyCompact::radman_auto,
	SkyCompact::burke_auto,
	SkyCompact::babs_auto,
	SkyCompact::dan_auto,
	SkyCompact::spu_auto,
	SkyCompact::medi_auto,
	SkyCompact::wit_auto,
	SkyCompact::gal_auto,
	SkyCompact::ken_auto
};