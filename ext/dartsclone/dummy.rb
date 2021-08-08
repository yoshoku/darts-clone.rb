# This class is for yard.

# Darts-clone.rb is a Ruby binding for the Darts-clone.
module DartsClone
  # The version of Darts-clone.rb you are using.
  VERSION = '0.2.2'

  # The version of Darts-clone that this gem is binding to.
  DARTS_CLONE_VERSION = '0.32'

  # DoubleArray is a class that implements double-array trie.
  #
  # @example
  #   require 'dartsclone'
  #
  #   da = DartsClone::DoubleArray.new
  #
  #   keys = ['abc', 'abcd', 'abcde', 'bcd', 'cde']
  #   da.build(keys)
  #
  #   p da.common_prefix_search('abcde')
  #   # => [["abc", "abcd", "abcde"], [0, 1, 2]]
  #
  class DoubleArray
    # Create a new double-array trie.
    def initialize; end

    # Build index of double-array trie
    #
    # @param keys [Array<String>]
    # @param values [Array<Integer>]
    # @return [Boolean]
    def build(keys, values: nil); end

    # Open saved index.
    #
    # @param filename [String]
    # @return [Boolean]
    def open(filename); end

    # Save index.
    #
    # @param filename [String]
    # @param mode [String]
    # @param offset [Integer]
    # @return [Boolean]
    def save(filename, mode: 'wb', offset: 0); end

    # Dump array data.
    #
    # @return [String]
    def get_array(); end

    # Load array data.
    #
    # @param str [String]
    def set_array(str); end

    # Search with exact match
    #
    # @param key [String]
    # @param length [Integer]
    # @param node_pos [Integer]
    def exact_match_search(key, length: 0, node_pos: 0); end

    # Common prefix search.
    #
    # @param key [String]
    def common_prefix_search(key, max_num_results: nil, length: 0, node_pos: 0); end

    # Traverse trie.
    #
    # @param key [String]
    def traverse(key, node_pos: nil, key_pos: nil, length: nil); end

    # size
    # @return [Integer]
    def unit_size(); end

    # unit size
    # @return [Integer]
    def size(); end

    # total size
    # @return [Integer]
    def total_size(); end

    # clear trie
    # @return [Nil]
    def clear(); end
  end
end

