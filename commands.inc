/**
 * TODO: Add top-level comment
 */

#if defined _command_manager_included
  #endinput
#endif
#define _command_manager_included

#tryinclude "../alias_t.inc"
#tryinclude "include/commands/alias_t.inc"
#tryinclude "include/commands-inc/alias_t.inc"
#if !defined _alias_t_included
  #include <alias_t>
#endif

#tryinclude "../command_t.inc"
#tryinclude "include/commands/command_t.inc"
#tryinclude "include/commands-inc/command_t.inc"
#if !defined _command_t_included
  #include <command_t>
#endif

#tryinclude "../commands_const.inc"
#tryinclude "include/commands/commands_const.inc"
#tryinclude "include/commands-inc/commands_const.inc"
#if !defined _commands_const_included
  #include <commands_const>
#endif

#pragma reqlib commands

/*******************************************************************************
 * FORWARDS
 ******************************************************************************/

/**
 * Called just before a command is called (i.e., when a command has been found
 * valid and other plugins are given an opportunity to reject it for some
 * outlying reason which can be set with {@link #cmd_setError}).
 *
 * @param id      The player who executed the command
 * @param prefix  The character which prefixed the command (e.g.,
 *                  {@code '/'} would be the value if {@code "/command"} were
 *                  the command)
 * @param command The command being executed
 *
 * @return {@code PLUGIN_HANDLED} will block the command, {@code PLUGIN_CONTINUE}
 *         otherwise. If the command is blocked, a reason should be specified
 *         using {@link #cmd_setError}
 */
forward cmd_onBeforeCommand(const id, const prefix, const Command: command);

/**
 * Called after a command has been processed (i.e., after the command is valid
 * and no plugin blocked it within its {@link #cmd_onBeforeCommand} forward)
 *
 * @param id      The player who executed the command
 * @param prefix  The character which prefixed the command (e.g.,
 *                  {@code '/'} would be the value if {@code "/command"} were
 *                  the command)
 * @param command The command being executed
 *
 * @noreturn
 */
forward cmd_onCommand(const id, const prefix, const Command: command);

/**
 * Called after a command has been registered.
 *
 * @param command    The unique identifier assigned to the command
 * @param alias      The alias that the command was registered with (i.e., the
 *                     text following a prefix, which when typed triggers
 *                     executes the command
 * @param flags      The flags which represent the conditions that must be met
 *                     for the command to be considered valid
 *                     (i.e., player states)
 * @param desc       A brief description of the command
 * @param adminFlags The privileges required to execute the command
 *
 * @noreturn
 */
forward cmd_onCommandRegistered(const Command: command, const alias[],
                                const flags[], const desc[], const adminFlags);

/**
 * Called after command prefixes have been modified.
 *
 * @param oldValue An array consisting of the old prefix characters
 * @param newValue An array consisting of the current prefix characters
 * 
 * @noreturn
 */
forward cmd_onPrefixesChanged(const oldValue[], const newValue[]);

/*******************************************************************************
 * NATIVES
 ******************************************************************************/

/**
 * Sets the error string for a command if it has been blocked using
 * {@link #cmd_onBeforeCommand}.
 * 
 * @param error The reason to the player why the command was rejected.
 * 
 * @throws IllegalStateException when called outside of
 *         {@link #cmd_onBeforeCommand}.
 */
native cmd_setError(const error[]);

/**
 * Registers a command with a default alias. The handle of the command will
 * be called with the following params if specified conditions are met and
 * another plugin doesn't block it: {@code id, player, args}.
 *     id     The player triggering the command 
 *     player The target player, or {@code 0} if no or multiple players are
 *              found by the name given, e.g., {@code /slay "Player"} will
 *              attempt to automatically parse the arguments ({@code "Player"})
 *              and return the index of the player named {@code "Player"} using
 *              {@link amxmisc.inc::#cmd_target}
 *     args   The text trailing the alias, e.g., {@code /slap "Player" 10} would
 *              result in {@code "Player" 10} with {@code player} set to the
 *              player index of the player named {@code "Player"} (if found)
 * 
 * Flags are:
 *     1 Execute only if command executed using {@code say}
 *     2 Execute only if command executed using {@code say_team}
 * 
 *     a Execute only if the player is alive
 *     d Execute only if the player is dead
 * 
 *     u Execute only if the player's team is UNASSIGNED
 *     t Execute only if the player's team is TERRORIST
 *     c Execute only if the player's team is CT
 *     s Execute only if the player's team is SPECTATOR
 * 
 * @param alias      The default alias of the command
 * @param handle     The name of the local callback function to call when the
 *                     command is executed
 * @param flags      The flags specifying the states a player must be in to
 *                     execute the command. Valid flags are listed above,
 *                     additionally,
 *                     {@link command_manager_const.inc::#FLAG_SEPARATOR}
 *                     can be used as a separator (i.e., no actual meaning)
 * @param desc       A brief description of the command (i.e., what it does)
 * @param adminFlags The admin privileges ({@code ADMIN_*} constants) required
 *                     to execute the command
 *
 * @return A unique identifier associated with the command, {@code Invalid_Command}
 *         otherwise if there was some problem registering the command (see logs
 *         for detailed information on the specific reason).
 */
native Command: cmd_registerCommand(
    const alias[],
    const handle[],
    const flags[] = "12,ad,utcs",
    const desc[] = "",
    const adminFlags = ADMIN_ALL);

/**
 * Registers an alias for a specified command, or rebinds the alias if it is
 * already bound.
 * 
 * @param command The command to associate {@code alias} with
 * @param alias   The alias to associate (bind with)
 *
 * @return The unique identifier of the alias, {@code Invalid_Alias} otherwise
 *         if there was some problem registering the alias (see logs for
 *         detailed information on the specific reason)
 */
native Alias: cmd_registerAlias(const Command: command, const alias[]);

/**
 * Returns the command associated with the specified {@code alias}.
 *
 * @param alias The alias to search for
 * 
 * @return The command which {@param alias} is associated with, or
 *         {@code Invalid_Command} if it is not yet bound to any command
 */
native Command: cmd_findCommand(const alias[]);

/**
 * Indicates whether or not the given value is a valid command identifier (i.e.,
 * is a identifier returned by {@link #cmd_registerCommand}).
 * 
 * @param command The value to check
 * 
 * @return {@code true} if it is a valid command identifer, {@code false} otherwise
 */
native bool: cmd_isValidCommand({any,Command}: command);

/**
 * Indicates whether or not the given value is a valid alias identifier (i.e.,
 * is a identifier returned by {@link #cmd_registerAlias}).
 * 
 * @param alias The value to check
 * 
 * @return {@code true} if it is a valid command identifer, {@code false} otherwise
 */
native bool: cmd_isValidAlias(const {any,Alias}: alias);

/**
 * Returns the number of commands registered.
 */
native cmd_getNumCommands();

/**
 * Returns the number of aliases registered.
 */
native cmd_getNumAliases();