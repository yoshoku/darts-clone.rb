# Darts-clone.rb

Darts-clone.rb is a Ruby binding for the [Darts-clone](https://github.com/s-yata/darts-clone).

## Installation

Add this line to your application's Gemfile:

```ruby
gem 'dartsclone'
```

And then execute:

    $ bundle install

Or install it yourself as:

    $ gem install dartsclone

## Usage

```ruby
require 'dartsclone'

da = DartsClone::DoubleArray.new

# Construct a dictionary.
keys = ['abc', 'abcd', 'abcde', 'bcd', 'cde']
da.build(keys)

# Search for keys which match the prefix of given string.
p da.common_prefix_search('abcde')
# => [["abc", "abcd", "abcde"], [0, 1, 2]]

# Search a key which matches a given string.
p da.exact_match_search('abcd')
# => 1

# Dump the dictionary.
da.save('foo.dat')

# Load the dictionary.
da.open('foo.dat')
```

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/yoshoku/darts-clone.rb.
This project is intended to be a safe, welcoming space for collaboration, and contributors are expected to adhere to the [code of conduct](https://github.com/yoshoku/darts-clone.rb/blob/master/CODE_OF_CONDUCT.md).

## License

The gem is available as open source under the terms of the [BSD 2-clause License](https://opensource.org/licenses/BSD-2-Clause).

## Code of Conduct

Everyone interacting in the Darts project's codebases, issue trackers, chat rooms and mailing lists is expected to follow the [code of conduct](https://github.com/yoshoku/darts-clone.rb/blob/master/CODE_OF_CONDUCT.md).
