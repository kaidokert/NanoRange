// Range v3 library
//
//  Copyright Eric Niebler 2014
//
//  Use, modification and distribution is subject to the
//  Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// Project home: https://github.com/ericniebler/range-v3
//
//  Copyright 2005 - 2007 Adobe Systems Incorporated
//  Distributed under the MIT License(see accompanying file LICENSE_1_0_0.txt
//  or a copy at http://stlab.adobe.com/licenses.html)

#include <nanorange/algorithm/merge.hpp>
#include <algorithm>
#include <memory>
#include <utility>
#include "../catch.hpp"
#include "../test_utils.hpp"

namespace stl2 = nano;

TEST_CASE("alg.merge")
{
	{
		unsigned N = 100000;
		std::unique_ptr<int[]> ia{new int[N]};
		std::unique_ptr<int[]> ib{new int[N]};
		std::unique_ptr<int[]> ic{new int[2 * N]};
		for(unsigned i = 0; i < N; ++i)
			ia[i] = 2 * i;
		for(unsigned i = 0; i < N; ++i)
			ib[i] = 2 * i + 1;
		auto r = stl2::merge(ia.get(), ia.get() + N,
			ib.get(), ib.get() + N, ic.get());
		CHECK(r.in1 == ia.get() + N);
		CHECK(r.in2 == ib.get() + N);
		CHECK(r.out == ic.get() + 2 * N);
		CHECK(ic[0] == 0);
		CHECK(ic[2 * N - 1] == (int)(2 * N - 1));
		CHECK(std::is_sorted(ic.get(), ic.get() + 2 * N));
	}

	{
		unsigned N = 100000;
		std::unique_ptr<int[]> ia{new int[N]};
		std::unique_ptr<int[]> ib{new int[N]};
		std::unique_ptr<int[]> ic{new int[2 * N]};
		for(unsigned i = 0; i < N; ++i)
			ia[i] = 2 * i;
		for(unsigned i = 0; i < N; ++i)
			ib[i] = 2 * i + 1;
		auto r0 = stl2::make_subrange(ia.get(), ia.get() + N);
		auto r1 = stl2::make_subrange(ib.get(), ib.get() + N);
		auto r = stl2::merge(r0, r1, ic.get());
		CHECK(r.in1 == ia.get() + N);
		CHECK(r.in2 == ib.get() + N);
		CHECK(r.out == ic.get() + 2 * N);
		CHECK(ic[0] == 0);
		CHECK(ic[2 * N - 1] == (int)(2 * N - 1));
		CHECK(std::is_sorted(ic.get(), ic.get() + 2 * N));
	}


	{
		unsigned N = 100000;
		std::unique_ptr<int[]> ia{new int[N]};
		std::unique_ptr<int[]> ib{new int[N]};
		std::unique_ptr<int[]> ic{new int[2 * N]};
		for(unsigned i = 0; i < N; ++i)
			ia[i] = 2 * i;
		for(unsigned i = 0; i < N; ++i)
			ib[i] = 2 * i + 1;
		auto r0 = stl2::make_subrange(ia.get(), ia.get() + N);
		auto r1 = stl2::make_subrange(ib.get(), ib.get() + N);
		auto r = stl2::merge(std::move(r0), std::move(r1), ic.get());
		CHECK(r.in1 == ia.get() + N);
		CHECK(r.in2 == ib.get() + N);
		CHECK(r.out == ic.get() + 2 * N);
		CHECK(ic[0] == 0);
		CHECK(ic[2 * N - 1] == (int)(2 * N - 1));
		CHECK(std::is_sorted(ic.get(), ic.get() + 2 * N));
	}
}
