# Require any additional compass plugins here.
require 'sassy-buttons'

# Set this to the root of your project when deployed:
http_path = "/"
css_dir = "styles"
sass_dir = "scss"
images_dir = "images"
javascripts_dir = "js"

# Remove all CSS files from sites/default/files/css when compass rebuilds
on_stylesheet_saved do |filename|
  sites_path = filename[/^.*drupal\/sites/]
  return if sites_path.nil?

  cache_dir = File.join(sites_path, 'default', 'files', 'css')
  did_clean = false

  Dir.entries(cache_dir).each do |cache_file|
    cache_file = File.join(cache_dir, cache_file)

    next if !File.file?(cache_file)
    next if cache_file.split('.').last.to_s.strip != 'css'

    File.unlink(cache_file)
    did_clean = true
  end

  puts "  >> Cleaned Drupal's CSS cache." if did_clean
end

# To enable relative paths to assets via compass helper functions. Uncomment:
# relative_assets = true
