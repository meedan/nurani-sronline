// $Id: README.txt,v 1.1.2.7 2009/08/16 17:52:46 doq Exp $

CONTENTS OF THIS FILE
---------------------

 * About
 * Features
 * Requirements
 * Optional requirements
 * Installation
 * More Information

<h2>ABOUT</h2>

"Cache" module provides bridge between Drupal and alternative cache handler
implementators: e.g. APC, memcache, redis.

It provides implementation of page_fast_cache() function.

<h2>FEATURES</h2>

- Additional cache handlers.
- page_fast_cache() implementation.
- hook_requirements() implementation. See report status of used
  cache handlers.
- Alternative session handler.
- Set of core patches to improve performance on big Drupal web-sites.
- In case all alternative cache handlers fail (e.g. no APC, memcache installed)
  it will use standard database caching. Administrator then may check
  "Status report" page and see why any of cache handler fails.
- Cache handlers chaining.


<h2>REQUIREMENTS</h2>

By default, "Cache" module doesn't require any additional cache handler
implementations. It will use database for cache storage as default
Drupal installation does.


<h2>OPTIONAL REQUIREMENTS</h2>

To gain all the features of "Cache" module you might want to install one
or more alternative cache handler engines:
  - PHP APC
  - memcache
  - redis


<h2>INSTALLATION</h2>

1. Enable "Cache" (from "Cache" package) module on
   Admininster -> Site building -> Modules page.

2. SETUP WEB-SITE'S settings.php CONFIGURATION FILE

   Add the following lines to your settings.php:

<?php
    $conf['cache_inc'] = './sites/all/modules/cache/cache.inc';
    $conf['cache_settings'] = array(
      'engines' => array(
        'database-engine' => array(
          'engine' => 'database',
        ),
      ),
      'schemas' => array(
        'database-schema' => array(
          'database-engine',
        )
      ),
      'bins' => array(
        'default' => 'database-schema',
      ),
    );
?>

"default" is for the default caching schema.  All valid cache bins (tables)
can be added in addition, but you must have a "default" if you skip any bins.

You can add several more cache schemas and use them for bins. Each schema is
array of arrays, each array is contains configuration of engine. If several
engines per schema is specified then cache chaining will be used: for example
if cache entry is not found in 1st engine then we'll try to find it in 2nd,
then in 3rd etc.

To enable alternative session handler you might want to add to web-site's
settings.php:

<code>
    $conf['session_inc'] = './sites/all/modules/cache/session.inc';
</code>

Then new bins "cache_session" and "cache_session_user" will be created. You may
configure any caching schema for them like for any other table.

To enable alternative path storage handler you might want to add to web-site's
settings.php:

<code>
    $conf['path_inc'] = './sites/all/modules/cache/path/path-max.inc';
</code>

or

<code>
    $conf['path_inc'] = './sites/all/modules/cache/path/path-cache.inc';
</code>

This feature also requires core patch "path_inc-variable-support.patch" to be applied.
It can be applied manually or applied through web administration using patchdoq
module if installed: Administer -> Site building -> Patch.

New bins "cache_path_alias" and "cache_path_source" will be created. You may
configure any caching schema for them like for any other table. Aware that
leaving it for default database engine might degrade performance.

   -----------------------------------------------------------------------------
   Engine configuration options:
   -----------------------------------------------------------------------------
   engine
     Type of engine. Valid values are:
       apc, db, file, null, memcache, memcached, redis, xcache, eaccelerator.
     Required.
     Note that eaccelerator engine is unmaintained currently.

   server
     (for memcache engine only) Array of memcached host:port combinations.
     Example:
<code>
       'server' => array('localhost:11211', 'localhost:11212')
</code>
     If none specified then default will be
<code>
       'server' => array('localhost:11211')
</code>
     You can also use unix sockets to connect to memcached server. Example usage:
<code>
       'server' => array('unix:///tmp/memcached.sock:0')
</code>
     Remember that unix socket should be readable / writable by web-server user.

     (for memcached engine only) Array of memcached host:port combinations.
     Example:
<code>
       'server' => array('localhost:11211', 'localhost:11212')
</code>
     If none specified then default will be
<code>
       'server' => array('localhost:11211')
</code>

     (for redis engine only) Array of redis host:port combinations. Currently
     only one host is allowed.
     Example:
       'server' => array('localhost:56379')
     If none specified then default will be
       'server' => array('localhost:6379')

   shared
     (for memcache and memcached engines) When enabled then locking mechanism is enabled
     and flushing works correctly (flushes only items it had set, not all).
     But these features degrade performance.
     You can set this parameter to FALSE. But separate cache server / cluster
     for each bin is recommended in such case.

     (for redis engine) When enabled then locking mechanism is enabled.
     Default is TRUE.

   prefix
     Used for unique site names usually when running multiple sites.
     If none specified then default will be empty string.

   static
     If TRUE then also cache fetched values in PHP static variable. Might
     increase performance when enabled for "cache_path_alias", "cache_path_source"
     cache bins.
     Default is FALSE.

   path
     (for file engine only) Path where to store cache.
     Default: /tmp/filecache

   flush_all
     (for memcache and memcached engines only) If TRUE then flushing of any bin will
     remove all the cache of specified cluster. You may want to
     assign separate clusters for every bin when using this feature.
     If FALSE then cache engine will keep list of keys that were set using the
     specified cache engine. So flushing will loop through list and remove
     specified records from the cache.
     But flush_all enabled - flushing will clear even records that were not
     scheduled for removal, e.g. those with CACHE_PERMANENT. So it might
     degrade performance.
     Default is FALSE.

   index
     (for redis only) Redis database index. For best performance you need to use
     unique index per every bin. e.g.
        cache - 0
        cache_page - 1
        cache_form - 2
        ...
     Of course this requires from you to list all bins in settings.php explicitly.
     Default is 0.

   clear
     (for memcache, memcached and redis only) Use this flag for debugging only or when you need
     to clear all the cache. Set it to TRUE. It degrades performance significantly
     since it clears all the cache on every page request.
     Default is FALSE.

   bin_per_db
     (for redis only) If TRUE then assume that every bin goes to separate Redis
     database. This improves performance because there is no need to keep track
     of every key added to perform correct flushing. But to work correctly
     'index' option is required to be set explicitly for every bin.
     Default is FALSE.

   fast_cache
     Turns page_fast_cache on.
     If you want to get anonymous usage statistics you should turn this option off.
     Default is TRUE. For database engine it's always FALSE and can't be turned on.

   -----------------------------------------------------------------------------

   Examples of working "Cache" module configuration:

   Example #1:

<?php
    $conf['cache_inc'] = './sites/all/modules/cache/cache.inc';
    $conf['session_inc'] = './sites/all/modules/cache/session.inc';
    $conf['cache_settings'] = array(
      'engines' => array(
        'db' => array(
          'engine' => 'database',
          'server' => array(),
          'shared' => TRUE,
          'prefix' => '',
        ),
        'apc' => array(
          'engine' => 'apc',
          'server' => array(),
          'shared' => TRUE,
          'prefix' => '',
        ),
        'memcache' => array(
          'engine' => 'memcache',
          'server' => array(
            'localhost:11211',
            'localhost:11212',
          ),
          'shared' => TRUE,
          'prefix' => '',
        ),
      ),

      'schemas' => array(
        'db' => array(
          // Engines:
          'db',
        ),
        'apc' => array(
          // Engines:
          'apc',
        ),
        'memcache' => array(
          // Engines:
          'memcache',
        ),
      ),

      'bins' => array(
        // Bin name     => Schema name.
        'default'       => 'db',
        'cache'         => 'apc',
        'cache_form'    => 'memcache',
        'cache_page'    => 'memcache',
        'cache_filter'  => 'memcache',
      ),
    );
?>


   Example #2 (with cache chaining - very rare usage case but may be useful):
<?php
    $conf['cache_inc'] = './sites/all/modules/cache/cache.inc';
    $conf['session_inc'] = './sites/all/modules/cache/session.inc';
    $conf['cache_settings'] = array(
      'engines' => array(
        'apc-engine' => array(
          'engine' => 'apc',
          'server' => array(),
          'shared' => TRUE,
          'prefix' => '',
        ),
        'memcache-engine' => array(
          'engine' => 'memcache',
          'server' => array(
            'localhost:11211',
            'localhost:11212',
          ),
          'shared' => TRUE,
          'prefix' => '',
        ),
        'db-engine' => array(
          'engine' => 'database',
          'server' => array(),
          'shared' => TRUE,
          'prefix' => '',
        ),
      ),
      'schemas' => array(
        'apc-memcache-db-schema' => array(
          // Engines:

          // Primary cache.
          'apc-engine',

          // Secondary cache.
          'memcache-engine',

          // Another secondary cache, in case both APC and memcache fail.
          'db-engine',
        ),

        'apc-schema' => array(
          // Engines:
          'apc-engine',
        ),
        'memcache-schema' => array(
          // Engines:
          'memcache-engine',
        ),
      ),
      'bins' => array(
        // Bin name     => Schema name.
        'default'       => 'memcache-schema',
        'cache'         => 'apc-schema',
        'cache_form'    => 'apc-memcache-db-schema',
        'cache_filter'  => 'my-memcache',
      ),

    );
?>


<h2>MORE INFORMATION</h2>

- For additional documentation, see the project page at
  http://drupal.org/project/cache
