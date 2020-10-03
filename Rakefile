require 'bundler/gem_tasks'
require 'rspec/core/rake_task'

RSpec::Core::RakeTask.new(:spec)

require 'rake/extensiontask'

task :build => :compile

Rake::ExtensionTask.new('dartscloneext') do |ext|
  ext.ext_dir = 'ext/dartsclone'
  ext.lib_dir = 'lib/dartsclone'
end

task :default => [:clobber, :compile, :spec]
