require 'bundler/gem_tasks'
require 'rspec/core/rake_task'

RSpec::Core::RakeTask.new(:spec)

require 'rake/extensiontask'

task :build => :compile

Rake::ExtensionTask.new('dartsext') do |ext|
  ext.ext_dir = 'ext/darts'
  ext.lib_dir = 'lib/darts'
end

task :default => [:clobber, :compile, :spec]
