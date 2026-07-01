# Third-Party Evidence

IIS LLM Store Bridge does not bundle third-party source libraries, model weights, cloud services, SDK redistributables, or executable dependencies.

The bridge compiles against Unreal Engine and the public APIs of Internal Index Service and LLM Store. Provider secrets, model selection, runtime modes, fallback policy, and cost controls remain owned by LLM Store.

Evidence notes:

- No `Source/ThirdParty` folder is shipped in this example project.
- No vendor binaries, model weights, or external service clients are shipped by the bridge.
- Runtime prerequisites are the companion Tiny Tool Development plugins named in the README.
