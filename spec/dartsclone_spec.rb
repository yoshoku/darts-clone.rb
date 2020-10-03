# frozen_string_literal: true

RSpec.describe DartsClone do
  it 'does something useful' do
    da = DartsClone::DoubleArray.new
    #da.build(['ab', 'abc', 'abcd', 'ghi'], [0, 1, 2, 3])
    #pp da.common_prefix_search('abc', 2)
    da.build(['あい', 'あいう', 'あいうえ', 'いうえ', 'えお'], values: [0, 1, 2, 3, 4])
    s, v = da.common_prefix_search('あいうえ', 256)
    p s.map { |v| v.force_encoding('UTF-8') }
    p da.exact_match_search('あいう')
    p da.exact_match_search('いうえ')
  end
end
