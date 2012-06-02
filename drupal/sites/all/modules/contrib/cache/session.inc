<?php
// $Id: session.inc,v 1.1.2.2 2009/08/06 14:54:11 doq Exp $

/**
 * @file
 * Experimental implementation of session handler.
 */

/**
 * @file
 * User session handling functions.
 *
 * Alternative implementation.
 */

function sess_open($save_path, $session_name) {
  return TRUE;
}

function sess_close() {
  return TRUE;
}

function sess_read($key) {
  global $user;

  // Write and Close handlers are called after destructing objects since PHP 5.0.5
  // Thus destructors can use sessions but session handler can't use objects.
  // So we are moving session closure before destructing objects.
  register_shutdown_function('session_write_close');

  // Handle the case of first time visitors and clients that don't store cookies (eg. web crawlers).
  if (!isset($_COOKIE[session_name()])) {
    $user = drupal_anonymous_user();
    return '';
  }

  $session = cache_get($key, 'cache_session');
//  var_dump($session);

  // Otherwise, if the session is still active, we have a record of the client's session in the database.
  if ($session && $session->data['uid'] != 0) {
    $user = db_fetch_object(db_query('SELECT u.* FROM {users} u WHERE u.uid = %d', $session->data['uid']));
  }

  // We found the client's session record and they are an authenticated user
  if ($session && $session->data['uid'] != 0 && $user && $user->uid > 0) {
    // This is done to unserialize the data member of $user
    $user = drupal_unpack($user);

    // Normally we would join the session and user tables. But we already
    // have the session information. So add that in.
    $user->sid = $session->data['sid'];
    $user->cache = $session->data['cache'];
    $user->hostname = $session->data['hostname'];
    $user->timestamp = $session->data['timestamp'];
    $user->session = strlen($session->data['session']) == 0 ? '' : $session->data['session'];

    // Add roles element to $user
    $user->roles = array();
    $user->roles[DRUPAL_AUTHENTICATED_RID] = 'authenticated user';
    $result = db_query("SELECT r.rid, r.name FROM {role} r INNER JOIN {users_roles} ur ON ur.rid = r.rid WHERE ur.uid = %d", $user->uid);
    while ($role = db_fetch_object($result)) {
      $user->roles[$role->rid] = $role->name;
    }
  }
  // We didn't find the client's record (session has expired), or they are an anonymous user.
  else {
    $session = isset($user->session) ? $user->session : '';
    $user = drupal_anonymous_user($session);
  }

  return $user->session;
}

function sess_write($key, $value) {
  global $user;

  // If saving of session data is disabled or if the client doesn't have a session,
  // and one isn't being created ($value), do nothing. This keeps crawlers out of
  // the session table. This reduces memory and server load, and gives more useful
  // statistics. We can't eliminate anonymous session table rows without breaking
  // the throttle module and the "Who's Online" block.
  if (!session_save_session() || ($user->uid == 0 && empty($_COOKIE[session_name()]) && empty($value))) {
    return TRUE;
  }

  $session = array(
    'uid' => $user->uid,
    'sid' => $key,
    'cache' => isset($user->cache) ? $user->cache : '',
    'hostname' => ip_address(),
    'session' => $value,
    'timestamp' => time(),
  );
  cache_set($key, $session, 'cache_session', time() + ini_get('session.gc_maxlifetime'));

  $cache = cache_get($user->uid, 'cache_session_user');
  $keys = array();
  if ($cache) {
    $keys = $cache->data;
  }
  $_k = array_search($key, $keys);
  if ($_k === FALSE) {
    $keys[] = $key;
  }
  cache_set($user->uid, $keys, 'cache_session_user', time() + ini_get('session.gc_maxlifetime'));

  // Last access time is updated no more frequently than once every 180 seconds.
  // This reduces contention in the users table.
  if ($user->uid && time() - $user->access > variable_get('session_write_interval', 180)) {
    db_query("UPDATE {users} SET access = %d WHERE uid = %d", time(), $user->uid);
  }

  return TRUE;
}

/**
 * Called when an anonymous user becomes authenticated or vice-versa.
 */
function sess_regenerate() {
  $old_session_id = session_id();

  // We code around http://bugs.php.net/bug.php?id=32802 by destroying
  // the session cookie by setting expiration in the past (a negative
  // value).  This issue only arises in PHP versions before 4.4.0,
  // regardless of the Drupal configuration.
  // TODO: remove this when we require at least PHP 4.4.0
  if (isset($_COOKIE[session_name()])) {
    setcookie(session_name(), '', time() - 42000, '/');
  }

  session_regenerate_id();

  $old_session = cache_get($old_session_id, 'cache_session');
  if ($old_session) {
    // Store it with the new key.
    $key = session_id();
    cache_set($key, $old_session->data, 'cache_session', time() + ini_get('session.gc_maxlifetime'));

    $cache = cache_get($old_session->data['uid'], 'cache_session_user');
    $keys = array();
    if ($cache) {
      $keys = $cache->data;
    }
    $_k = array_search($old_session_id, $keys);
    if ($_k !== FALSE) {
      unset($keys[$_k]);
    }
    $keys[] = $key;
    cache_set($old_session->data['uid'], $keys, 'cache_session_user', time() + ini_get('session.gc_maxlifetime'));
  }

  // Clear the old data from the cache.
  cache_clear_all($old_session_id, 'cache_session');
  cache_clear_all($old_session_id, 'cache_session_user');
}

/**
 * Counts how many users have sessions. Can count either anonymous sessions or authenticated sessions.
 *
 * @param int $timestamp
 *   A Unix timestamp representing a point of time in the past.
 *   The default is 0, which counts all existing sessions.
 * @param boolean $anonymous
 *   TRUE counts only anonymous users.
 *   FALSE counts only authenticated users.
 * @return  int
 *   The number of users with sessions.
 */
function sess_count($timestamp = 0, $anonymous = true) {
//  $query = $anonymous ? ' AND uid = 0' : ' AND uid > 0';
//  return db_result(db_query('SELECT COUNT(sid) AS count FROM {sessions} WHERE timestamp >= %d'. $query, $timestamp));
  /// @todo Not implemented.
  return 0;
}

/**
 * Called by PHP session handling with the PHP session ID to end a user's session.
 *
 * @param  string $sid
 *   the session id
 */
function sess_destroy_sid($sid) {
  cache_clear_all($sid, 'cache_session');
}

/**
 * End a specific user's session
 *
 * @param  string $uid
 *   the user id
 */
function sess_destroy_uid($uid) {
  $cache = cache_get($uid, 'cache_session_user');
  if ($cache) {
    foreach ($cache->data as $session_id) {
      cache_clear_all($session_id, 'cache_session');
    }
    cache_clear_all($uid, 'cache_session_user');
  }
}

function sess_gc($lifetime) {
  // Be sure to adjust 'php_value session.gc_maxlifetime' to a large enough
  // value. For example, if you want user sessions to stay in your database
  // for three weeks before deleting them, you need to set gc_maxlifetime
  // to '1814400'. At that value, only after a user doesn't log in after
  // three weeks (1814400 seconds) will his/her session be removed.
  return TRUE;
}

/**
 * Determine whether to save session data of the current request.
 *
 * This function allows the caller to temporarily disable writing of session data,
 * should the request end while performing potentially dangerous operations, such as
 * manipulating the global $user object.  See http://drupal.org/node/218104 for usage
 *
 * @param $status
 *   Disables writing of session data when FALSE, (re-)enables writing when TRUE.
 * @return
 *   FALSE if writing session data has been disabled. Otherwise, TRUE.
 */
function session_save_session($status = NULL) {
  static $save_session = TRUE;
  if (isset($status)) {
    $save_session = $status;
  }
  return ($save_session);
}
