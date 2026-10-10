#include <glm/gtc/matrix_transform.hpp>



class ITransformation {
public:
    virtual glm::mat4 getMatrix() const = 0;
    virtual ~ITransformation() = default;
};