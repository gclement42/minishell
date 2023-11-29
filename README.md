<h1>Minishell - A Beautiful Shell</h1>

<h2>Introduction</h2>
<p>Minishell is a projet make with <a href="https://github.com/JulesLaisne"> JulesLaisne </a>, objectif is create a command-line interface project that allows users to interact with a computer through a user-friendly shell. Developed in C, this project takes inspiration from the historical context when developers sought an alternative to the cumbersome 1/0 switches for computer communication.</p>

<h2>Project Highlights</h2>
<ul>
    <li><strong>Prompt Display:</strong> Minishell displays a prompt when waiting for a new command, providing an intuitive interface for users.</li>
    <li><strong>History Feature:</strong> The shell includes a working history feature, allowing users to access previously entered commands easily.</li>
    <li><strong>Command Execution:</strong> Minishell can search and launch the correct executable based on the PATH variable or a specified path.</li>
    <li><strong>Global Variable Usage:</strong> Careful usage of global variables is implemented to indicate received signals without compromising data structures.</li>
    <li><strong>Quoting Handling:</strong> Minishell avoids interpreting unclosed quotes or unnecessary special characters for a seamless user experience.</li>
    <li><strong>Redirections:</strong> The shell supports input and output redirections, including <code>&lt;</code>, <code>&gt;</code>, <code>&lt;&lt;</code>, and <code>&gt;&gt;</code>.</li>
    <li><strong>Pipes:</strong> Minishell allows users to create command pipelines using the <code>|</code> character, enhancing command flexibility.</li>
    <li><strong>Environment Variables:</strong> The shell intelligently handles the expansion of environment variables for robust functionality.</li>
    <li><strong>Special Variables:</strong> Minishell includes support for special variables, such as <code>$?</code>, expanding to the exit status of the most recently executed foreground pipeline.</li>
    <li><strong>Ctrl-C, Ctrl-D, Ctrl-\ Handling:</strong> Mimicking behavior similar to bash, Minishell appropriately handles these control characters in interactive mode.</li>
    <li><strong>Built-in Commands:</strong> The shell incorporates essential built-in commands, including <code>echo</code>, <code>cd</code>, <code>pwd</code>, <code>export</code>, <code>unset</code>, <code>env</code>, and <code>exit</code>.</li>
</ul>

<h2>Usage</h2>
<ol>
    <li><strong>Clone the Repository:</strong></li>
    <pre><code>git clone &lt;repository-url&gt;
cd minishell
</code></pre>
        <li><strong>Build the Project:</strong></li>
        <pre><code>make
</code></pre>
        <li><strong>Run Minishell:</strong></li>
        <pre><code>./minishell
</code></pre>
        <li><strong>Explore the Features:</strong></li>
        <ul>
            <li>Enter commands, use quotes, handle redirections and pipes.</li>
            <li>Try built-in commands like <code>cd</code>, <code>echo</code>, <code>env</code>, and others.</li>
        </ul>
</ol>
