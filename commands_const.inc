/**
 * Contains definitions and stocks related to commands and dealing with flags
 * associated with commands.
 */

#if defined _commands_const_included
    #endinput
#endif
#define _commands_const_included

#include "include/stocks/flag_stocks.inc"

/*******************************************************************************
 * DEFINITIONS
 ******************************************************************************/

#define FLAG_METHOD_SAY      1
#define FLAG_METHOD_SAY_TEAM 2

#define FLAG_STATE_ALIVE     3
#define FLAG_STATE_DEAD      4

#define FLAG_TEAM_UNASSIGNED 5
#define FLAG_TEAM_T          6
#define FLAG_TEAM_CT         7
#define FLAG_TEAM_SPECTATOR  8

#define FLAG_SEPARATOR          ','

#define FLAG_METHOD_SAY_CH      '1'
#define FLAG_METHOD_SAY_TEAM_CH '2'

#define FLAG_STATE_ALIVE_CH     'a'
#define FLAG_STATE_DEAD_CH      'd'

#define FLAG_TEAM_UNASSIGNED_CH 'u'
#define FLAG_TEAM_T_CH          't'
#define FLAG_TEAM_CT_CH         'c'
#define FLAG_TEAM_SPECTATOR_CH  's'

/*******************************************************************************
 * STOCKS
 ******************************************************************************/

stock readCustomFlags(const flags[], Logger: logger = Invalid_Logger) {
  new bits = 0;
  for (new i = 0, ch = flags[i]; ch != EOS; ch = flags[++i]) {
    switch (ch) {
      case FLAG_METHOD_SAY_CH:      setFlag(bits, FLAG_METHOD_SAY, logger);
      case FLAG_METHOD_SAY_TEAM_CH: setFlag(bits, FLAG_METHOD_SAY_TEAM, logger);

      case FLAG_STATE_ALIVE_CH:     setFlag(bits, FLAG_STATE_ALIVE, logger);
      case FLAG_STATE_DEAD_CH:      setFlag(bits, FLAG_STATE_DEAD, logger);

      case FLAG_TEAM_UNASSIGNED_CH: setFlag(bits, FLAG_TEAM_UNASSIGNED, logger);
      case FLAG_TEAM_T_CH:          setFlag(bits, FLAG_TEAM_T, logger);
      case FLAG_TEAM_CT_CH:         setFlag(bits, FLAG_TEAM_CT, logger);
      case FLAG_TEAM_SPECTATOR_CH:  setFlag(bits, FLAG_TEAM_SPECTATOR, logger);

      case FLAG_SEPARATOR:          continue;

      default: continue;
    }
  }

  return bits;
}

stock getCustomFlags(const bits, flags[], len, Logger: logger = Invalid_Logger) {
  new copyLen = 0;
  if (isFlagSet(bits, FLAG_METHOD_SAY, logger) && copyLen <= len) {
    flags[copyLen++] = FLAG_METHOD_SAY_CH;
  }

  if (isFlagSet(bits, FLAG_METHOD_SAY_TEAM, logger) && copyLen <= len) {
    flags[copyLen++] = FLAG_METHOD_SAY_TEAM_CH;
  }

  if (isFlagSet(bits, FLAG_STATE_ALIVE, logger) && copyLen <= len) {
    flags[copyLen++] = FLAG_STATE_ALIVE_CH;
  }

  if (isFlagSet(bits, FLAG_STATE_DEAD, logger) && copyLen <= len) {
    flags[copyLen++] = FLAG_STATE_DEAD_CH;
  }

  if (isFlagSet(bits, FLAG_TEAM_UNASSIGNED, logger) && copyLen <= len) {
    flags[copyLen++] = FLAG_TEAM_UNASSIGNED_CH;
  }

  if (isFlagSet(bits, FLAG_TEAM_T, logger) && copyLen <= len) {
    flags[copyLen++] = FLAG_TEAM_T_CH;
  }

  if (isFlagSet(bits, FLAG_TEAM_CT, logger) && copyLen <= len) {
    flags[copyLen++] = FLAG_TEAM_CT_CH;
  }

  if (isFlagSet(bits, FLAG_TEAM_SPECTATOR, logger) && copyLen <= len) {
    flags[copyLen++] = FLAG_TEAM_SPECTATOR_CH;
  }

  flags[copyLen + 1] = EOS;
  return copyLen;
}

stock CsTeams: getTeamForFlag(flag) {
  switch (flag) {
    case FLAG_TEAM_UNASSIGNED: return CS_TEAM_UNASSIGNED;
    case FLAG_TEAM_T:          return CS_TEAM_T;
    case FLAG_TEAM_CT:         return CS_TEAM_CT;
    case FLAG_TEAM_SPECTATOR:  return CS_TEAM_SPECTATOR;
  }

  return CS_TEAM_UNASSIGNED;
}

stock getFlagForTeam(CsTeams: team) {
  switch (team) {
    case CS_TEAM_UNASSIGNED: return FLAG_TEAM_UNASSIGNED;
    case CS_TEAM_T:          return FLAG_TEAM_T;
    case CS_TEAM_CT:         return FLAG_TEAM_CT;
    case CS_TEAM_SPECTATOR:  return FLAG_TEAM_SPECTATOR;
  }

  return 0;
}