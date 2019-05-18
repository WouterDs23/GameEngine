#pragma once
namespace dae
{
	class SceneObject
	{
	public:
		virtual void Update() = 0;
		virtual void Render() const = 0;

		bool GetDoRenderAndUpdate() const { return  m_RenderAndUpdate; }
		void SetDoRenderAndUpdate(bool doIDo) { m_RenderAndUpdate = doIDo; }

		SceneObject() = default;
		virtual ~SceneObject() = default;
		SceneObject(const SceneObject& other) = delete;
		SceneObject(SceneObject&& other) = delete;
		SceneObject& operator=(const SceneObject& other) = delete;
		SceneObject& operator=(SceneObject&& other) = delete;
	private:
		bool m_RenderAndUpdate{ true };
	};
}
