require_relative 'lib/darts/version'

Gem::Specification.new do |spec|
  spec.name          = 'darts-clone-rb'
  spec.version       = Darts::VERSION
  spec.authors       = ['yoshoku']
  spec.email         = ['yoshoku@outlook.com']

  spec.summary       = 'Ruby binding for the Darts-clone.'
  spec.description   = 'darts-clone.rb is a Ruby binding for the Darts-clone.'
  spec.homepage      = 'https://github.com/yoshoku/darts-clone.rb'
  spec.license       = 'BSD-2-Clause'

  spec.metadata['homepage_uri'] = spec.homepage
  spec.metadata['source_code_uri'] = spec.homepage
  spec.metadata['changelog_uri'] = 'https://github.com/yoshoku/darts-clone.rb/blob/master/CHANGELOG.md'

  # Specify which files should be added to the gem when it is released.
  # The `git ls-files -z` loads the files in the RubyGem that have been added into git.
  spec.files         = Dir.chdir(File.expand_path('..', __FILE__)) do
    `git ls-files -z`.split("\x0").reject { |f| f.match(%r{^(test|spec|features)/}) }
  end
  spec.bindir        = 'exe'
  spec.executables   = spec.files.grep(%r{^exe/}) { |f| File.basename(f) }
  spec.require_paths = ['lib']
  spec.extensions    = ['ext/darts/extconf.rb']
end
