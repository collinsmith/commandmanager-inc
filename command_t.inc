/**
 * Defines the template and constants for a command.
 */

#if defined _command_t_included
  #endinput
#endif
#define _command_t_included

/*******************************************************************************
 * command_t template
 ******************************************************************************/

/**
 * Definition to permit the {@code Cmd} tag in place of the {@code Command} tag.
 */
#define Cmd: Command:

/**
 * Tag used to identify commands.
 */
enum Command {
  /**
   * Constant representing the value used for a command which is invalid.
   */
  Invalid_Command
};

/**
 * Defines the maximum length for the description field of a command
 */
#define command_Desc_length 255

/**
 * Template defining the fields associated with a command.
 */
enum command_t {
  /**
   * A description of the command
   */
  command_Desc[command_Desc_length+1],

  /**
   * The player flags required for executing the command.
   */
  command_Flags,

  /**
   * The privileges required for executing the command.
   */
  command_AdminFlags,

  /**
   * The plugin which owns the callback function to be executed.
   */
  command_PluginID,

  /**
   * The callback functioin to be called when executing.
   */
  command_FuncID,

  /**
   * A list of aliases for this command.
   */
  Array: command_Aliases,
};