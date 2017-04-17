/**
 * Defines the template and constants for a command alias.
 */

#if defined _alias_t_included
  #endinput
#endif
#define _alias_t_included

#tryinclude "../command_t.inc"
#tryinclude "include/commands/command_t.inc"
#tryinclude "include/commands-inc/command_t.inc"
#if !defined _command_t_included
  #include <command_t>
#endif

/*******************************************************************************
 * alias_t template
 ******************************************************************************/

/**
 * Tag used to identify aliases.
 */
enum Alias {
  /**
   * Constant representing the value used for an alias which is invalid.
   */
  Invalid_Alias
};

/**
 * Defines the maximum length for the alias field of an alias
 */
#define alias_String_length 31

/**
 * Template defining the fields associted with an alias.
 */
enum alias_t {
  /**
   * The alias of the command.
   */
  alias_String[alias_String_length + 1],

  /**
   * The command associated with this alias.
   */
  Command: alias_Command,
};