#ifndef _ENGINE_SHADER_H_
#define _ENGINE_SHADER_H_

#include "../Config.h"

#include "../Internal/Shading/ShaderPlatform.h"

#include <string>

namespace Engine
{
	enum class ShaderStage : ShaderStageEnum_t
	{
		Invalid                 = 0,
		Vertex                  = ShaderVertex_v,
		TesselationControl      = ShaderTessCtrl_v,
		TesselationEvaluation   = ShaderTessEval_v,
		Geometry                = ShaderGeometry_v,
		Fragment                = ShaderFragment_v
	};

	class ENGINE_DYNAMIC_CLASS Shader : public ShaderPlatform
	{
	public:
		Shader(const Shader &other) = delete;
		Shader& operator=(const Shader &other) = delete;

		Shader();
		Shader(Shader&& other);
		
		virtual ~Shader();

		void setSource(const std::string &source, ShaderStage stage);
		bool compile();

		void clear();

		Shader& operator=(Shader&& other);
	};
}

#endif // _ENGINE_SHADER_H_