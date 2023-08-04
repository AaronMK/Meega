Rename "Local_template.props" to "Local.props" before opening the solution.  This contains paths to external dependencies to be filled in with locations on the local machine.

When using Meega as an SDK in another project, add the appropriate *.props file to your projects using the property manager.  This properly configures the headers for the external libraries.  Use as follows:

- MeegaDevelopment.props: This applies relevent build settings for the development build of the library.  This also includes MeegaDynamic.props.

- MeegaDynamic.props: This applies relevent build settings for a dynamically linked Meega SDK.

