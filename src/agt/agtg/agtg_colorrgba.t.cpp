#include <agtg_colorrgba.h>
#include <aunit.h>

namespace agtg {

using namespace aunit;

Describe d("agtg_colorrgba", []
{
    it("Constructor", [&]
    {
        agtg::ColorRGBA<double> white(0xffffffff);

        expect(white.red()).toEqual(1.0);
        expect(white.green()).toEqual(1.0);
        expect(white.blue()).toEqual(1.0);
        expect(white.alpha()).toEqual(1.0);

        agtg::ColorRGBA<double> red(255, 0, 0);

        expect(red.red()).toEqual(1.0);
        expect(red.green()).toEqual(0.0);
        expect(red.blue()).toEqual(0.0);
        expect(red.alpha()).toEqual(1.0);

        agtg::ColorRGBA<double> darkGreenHalfAlpha(0, .5, 0, 0.5);

        expect(darkGreenHalfAlpha.red()).toEqual(0.0);
        expect(darkGreenHalfAlpha.green()).toEqual(0.5);
        expect(darkGreenHalfAlpha.blue()).toEqual(0.0);
        expect(darkGreenHalfAlpha.alpha()).toEqual(0.5);
    });
});

} // namespace
