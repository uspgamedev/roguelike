#ifndef HORUSEYE_FRAMEWORK_FONT_H_
#define HORUSEYE_FRAMEWORK_FONT_H_

#include <string>
#include <ugdk/math/vector2D.h>
#include <ugdk/graphic.h>


namespace ugdk {
namespace graphic {

class Font {
  public:
	enum IdentType {
		LEFT,
		CENTER,
		RIGHT
	};
	Font(Texture** letters, int fontsize, char ident, bool fancy);
	~Font();
	int id() { return id_; }
	IdentType ident() { return ident_; }
	Vector2D GetLetterSize(wchar_t letter);
	bool IsFancy() { return fancy_;}

  private:
	int id_;
	int size_;
	Texture** letters_;
	IdentType ident_;
	bool fancy_;
};


}  // namespace graphic
}  // namespace ugdk

#endif
