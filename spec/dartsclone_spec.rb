# frozen_string_literal: true

RSpec.describe DartsClone::DoubleArray do
  let(:da) { described_class.new }
  let(:keys) { %w[東京 東京都 東京都中野区 東京都庁] }
  let(:vals) { [4, 3, 2, 1] }

  describe '#common_prefix_search' do
    context 'when building dictionary without values' do
      before { da.build(keys) }

      it 'returns search result', :aggregate_failures do
        k, v = da.common_prefix_search('東京都中野区')
        expect(k).to match(%w[東京 東京都 東京都中野区])
        expect(v).to match([0, 1, 2])
        k, v = da.common_prefix_search('東京都庁')
        expect(k).to match(%w[東京 東京都 東京都庁])
        expect(v).to match([0, 1, 3])
        k, v = da.common_prefix_search('東京都庁', max_num_results: 2)
        expect(k).to match(%w[東京 東京都])
        expect(v).to match([0, 1])
        expect(da.common_prefix_search('東')).to be_empty
      end
    end

    context 'when building dictionary with values' do
      before { da.build(keys, values: vals) }

      it 'returns search result with specified values', :aggregate_failures do
        k, v = da.common_prefix_search('東京都中野区')
        expect(k).to match(%w[東京 東京都 東京都中野区])
        expect(v).to match([4, 3, 2])
        k, v = da.common_prefix_search('東京都庁')
        expect(k).to match(%w[東京 東京都 東京都庁])
        expect(v).to match([4, 3, 1])
        k, v = da.common_prefix_search('東京都庁', max_num_results: 2)
        expect(k).to match(%w[東京 東京都])
        expect(v).to match([4, 3])
        expect(da.common_prefix_search('東')).to be_empty
      end
    end
  end

  describe '#exact_match_search' do
    context 'when building dictionary without values' do
      before { da.build(keys) }

      it 'returns search result', :aggregate_failures do
        expect(da.exact_match_search('東京都中野区')).to eq(2)
        expect(da.exact_match_search('東京都')).to eq(1)
        expect(da.exact_match_search('東')).to eq(-1)
      end
    end

    context 'when building dictionary with values' do
      before { da.build(keys, values: vals) }

      it 'returns search result with specified values', :aggregate_failures do
        expect(da.exact_match_search('東京都中野区')).to eq(2)
        expect(da.exact_match_search('東京都')).to eq(3)
        expect(da.exact_match_search('東')).to eq(-1)
      end
    end
  end

  describe '#save and #open' do
    let(:filename) { File.expand_path(__dir__ + '/foo.dat') }

    before { da.build(keys, values: vals) }

    it 'saves and loads dictionary', :aggregate_failures do
      da.save(filename)
      da.clear
      da.open(filename)
      k, v = da.common_prefix_search('東京都中野区')
      expect(k).to match(%w[東京 東京都 東京都中野区])
      expect(v).to match([4, 3, 2])
      expect(da.exact_match_search('東京都')).to eq(3)
    end
  end

  describe '#clear' do
    before { da.build(keys, values: vals) }

    it 'raises RuntimeError when searching after calling clear method', :aggregate_failures do
      expect(da.size).not_to eq(0)
      expect(da.total_size).not_to eq(0)
      da.clear
      expect(da.size).to eq(0)
      expect(da.total_size).to eq(0)
      expect { da.common_prefix_search('東京都') }.to raise_error(RuntimeError)
      expect { da.exact_match_search('東京都') }.to raise_error(RuntimeError)
    end
  end
end
