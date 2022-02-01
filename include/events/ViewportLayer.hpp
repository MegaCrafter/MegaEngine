#include "events/Layer.hpp"

namespace Engine {

class ViewportLayer : public Layer {
   public:
    virtual bool process_event(const Event& event) const override;
};

}  // namespace Engine