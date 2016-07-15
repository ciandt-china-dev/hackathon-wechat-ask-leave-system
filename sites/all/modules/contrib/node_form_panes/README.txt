Node Form Panes
---------------

Exposes node form elements as panel panes. Actually, technically we're creating ctools content types (no, not Drupal content types @see https://drupal.org/node/1197790) that panels turns into panes. *see 'Disclaimer' below for more information.

Currently ctools exposes node fields and core form elements that usually appear in vertical tabs as individual panes. However, it's missing support for any elements added to vertical tabs from contrib modules (e.g. Metatags, Scheduler, Redirect etc.). This module aims to supply some support for these modules.

This module was originally developed for the Sprout Install Profile (https://drupal.org/sandbox/codi/2012066)


Currently Supported Contrib Modules:
------------------------------------

- Metatgs
- Redirect
- Scheduler
- Rabbit Hole

Is there a contrib module whose node form element needs to be pane'd? Open a ticket in the Issue queue! Or better yet, submit a patch!


Core Node Form Elements
-----------------------

We also override the core vertical tab panes provided by ctools, adding the option to display the element in a fieldset.


Extras
------

As an added bonus there is a new pane "Node form summary" that combines some of the other form elements into one pane. You can see an example of what this can do to your content add/edit form in the image on the right. The options are:

- Include form buttons in summary block.
- Include a summary for if the node is published or not
- Include the "Authored by" field
- Include the "Authored on" field
- Include the "Promoted to front page" field
- Include the "Sticky at top of lists" field
- Add scheduler support for "Authored on" field


Disclaimer
----------

As mentioned above, this module doesn't technically create panes. It creates new ctools plugins known as "Content Types" that panels makes available as panes. Panels is not actually a dependency of Node Form Panes. Any other modules that support ctools content types will also have access to these plugins.

So why call the module Node Form Panes? I originally went with Node Form Panes because I specifically needed it for panels. Additionally I feel that most regular users will probably be implementing this as panel panes and I wanted it to be easy to find in searches. I don't know if most Panels users know whether they're adding a ctools content type or not to their panels. If you disagree, let's talk about it in the Issue Queue.


Credits
-------

Maintained by Chris Eastwood (drclaw)
Development is sponsored by Fuse Interactive
